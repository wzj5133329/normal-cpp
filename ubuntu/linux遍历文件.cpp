void scanFile(string szDir,vector<string>& files,vector<string> &filenames,int &count)
{
    
    DIR *pDir = NULL;
    struct dirent *pFile = NULL;
    
    pDir = opendir(szDir.c_str());
    if (pDir == NULL) return;
    
    while ((pFile = readdir(pDir)) != NULL) {
        if (pFile->d_type & DT_DIR) {
            if (strcmp(pFile->d_name, ".") == 0 
                || strcmp(pFile->d_name, "..") == 0) continue;
            
            char Path[256];
            int len = strlen(szDir.c_str());
            strncpy(Path, szDir.c_str(), len + 1);
            if (szDir.c_str()[len - 1] != '/') strncat(Path, "/", 2);
            strncat(Path, pFile->d_name, strlen(pFile->d_name) + 1);
            scanFile(Path,files,filenames,count);
        } else {
            string file = szDir+"/"+pFile->d_name;
            string filename =pFile->d_name;
            files.push_back(file);
            filenames.push_back(filename);
            ++count;
            //printf("path:%s     fileName:%s\n", szDir, pFile->d_name);
        }

    }
    
    closedir(pDir);
}