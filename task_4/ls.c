#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <sys/sysmacros.h>
#include <grp.h>
#include <string.h>
#include <sys/stat.h>

#define PATH_MAX 4096

void print_dir(const char *path, int l_flag, int r_flag, int g_flag, int header);
void long_list(int g_flag, const char *path_name);
void display_permission(int st_mode);
void display_file_type(int st_mode);

int main(int argc, char *argv[]) {
	int i;
	int l_flag = 0;
	int r_flag = 0;
	int g_flag = 0;
	
	for (i = 1; i < argc; i++) 
		if ((argv[i][0] == '-') && (strlen(argv[i])) == 2) {
			
			switch (argv[i][1]) {
				case 'l': l_flag = 1; break;
				case 'R': r_flag = 1; break;
				case 'g': g_flag = 1; break;
			}
		} else break;

	if (i >= argc)
		print_dir(".", l_flag, r_flag, g_flag, 0);
	else {
	
		int is_first = 1;

		for (; i < argc; i++) {
			struct stat sbuf;

			if (stat(argv[i], &sbuf) == -1) 
				fprintf(stderr, "%s: cannot open '%s'\n", argv[0], argv[i]);	

			else {
				if (S_ISDIR(sbuf.st_mode)) {
					if (!is_first)
						printf("\n");

					if (argc - i > 1) 
						printf("%s:\n", argv[i]);
					
					print_dir(argv[i], l_flag, r_flag, g_flag, 0);
					is_first = 0;
				} else
					if (l_flag || g_flag) 
						long_list(g_flag, argv[i]);
					else
						printf("%s\n", argv[i]);
			}
		}
	}
}
	
	void print_dir(const char *path, int l_flag, int r_flag, int g_flag, int header) {
		
		DIR *dir;
		struct dirent *dir_ent;
		dir = opendir(path);

		if (header)
			printf("\n%s:\n", path);

		if (dir == NULL) {
			fprintf(stderr, "ls: cannot open directory '%s'\n", path);
			exit(1);
		}
		
		while ((dir_ent = readdir(dir)) != NULL) {
			if (dir_ent->d_name[0] == '.') 
				continue;
				
			char newpath[PATH_MAX];
			snprintf(newpath, sizeof(newpath), "%s/%s", path, dir_ent->d_name);

			if (l_flag || g_flag) 
				long_list(g_flag, newpath);
			else 
				printf("%s  ", dir_ent->d_name);
		}		
		
		closedir(dir);
				
		if (r_flag) {	
			dir = opendir(path);	

			if (dir == NULL)
				return;

			while ((dir_ent = readdir(dir)) != NULL) {
				if (dir_ent->d_name[0] == '.' || strcmp(dir_ent->d_name, ".") == 0 || strcmp(dir_ent->d_name, "..") == 0)
					continue;
							
				char newpath[PATH_MAX];

				snprintf(newpath, sizeof(newpath), "%s/%s", path, dir_ent->d_name);
				
				struct stat sbuf;	
				if (stat(newpath, &sbuf) == 0 && S_ISDIR(sbuf.st_mode))	{
					printf("\n%s:\n", newpath);
					print_dir(newpath, l_flag, r_flag, g_flag, 0);
				}
			}
			closedir(dir);
		}
	}
			
	void display_file_type (int st_mode){                                   
    	
		switch (st_mode & S_IFMT) {
        	case S_IFDIR:  putchar ('d'); return;
        	case S_IFCHR:  putchar ('c'); return;
        	case S_IFBLK:  putchar ('b'); return;
        	case S_IFREG:  putchar ('-'); return;
        	case S_IFLNK:  putchar ('l'); return;
        	case S_IFSOCK: putchar ('s'); return;
    	}
	}

	void display_permission (int st_mode){
    	
		static const char xtbl[10] = "rwxrwxrwx";
    	char amode[10];
    	int i, j;

    	for (i = 0, j = (1 << 8); i < 9; i++, j >>= 1)
        	amode[i] = (st_mode & j) ? xtbl[i]: '-';

    	if (st_mode & S_ISUID) amode[2]= 's';
    	if (st_mode & S_ISGID) amode[5]= 's';
    	if (st_mode & S_ISVTX) amode[8]= 't';

  		amode[9] = '\0';
  		printf("%s ", amode);
	}


	void long_list (int g_flag, const char *path_name) {
		struct stat statv;
		struct passwd *pw_d;
 		struct group *gr_d;

		if (lstat(path_name, &statv) == -1) { 
    		perror(path_name); 
    		return;
  		}

	    display_file_type(statv.st_mode);
  		display_permission(statv.st_mode);
  		printf("%ld ", statv.st_nlink); 

  		pw_d = getpwuid(statv.st_uid); 
  			printf("%s ", pw_d->pw_name); 
 
		if (!g_flag) {
			gr_d = getgrgid(statv.st_gid);
				printf("%s ", gr_d->gr_name);
		}

  		if ((statv.st_mode & S_IFMT) == S_IFCHR || (statv.st_mode & S_IFMT) == S_IFBLK)
    		printf("%d, %d", major(statv.st_rdev), minor(statv.st_rdev));
			
  		else
    		printf ("%8ld ", statv.st_size);
  		
		const char *filename = strrchr(path_name, '/');
		if (filename)
			filename++;
		else
			filename = path_name;

  		printf("%s\n", filename);
	}
	
