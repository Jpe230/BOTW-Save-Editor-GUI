#include <string.h>
#include <stdio.h>
#include <dirent.h>

#include <switch.h>



void unmountSaveData(){
    fsdevCommitDevice("save");
    fsdevUnmountDevice("save");
}

int mountSaveData()
{
    int ret=0;
    Result rc = 0;

    FsFileSystem tmpfs;
    u128 userID=0;
    bool account_selected=0;
    u64 titleID=0x01007ef00011e000;

    rc = accountInitialize();
    
    if (R_FAILED(rc)) {
        printf("accountInitialize() failed: 0x%x\n", rc);
        return 0;
    }

    if (R_SUCCEEDED(rc)) {
        rc = accountGetActiveUser(&userID, &account_selected);
        accountExit();

     if (R_FAILED(rc)) {
            printf("accountGetActiveUser() failed: 0x%x\n", rc);
            return 0;
        }
     else if(!account_selected) {
            printf("No user is currently selected.\n");
            rc = -1;
            return 0;
        }
    }

    if (R_SUCCEEDED(rc)) {
        printf("Using titleID=0x%016lx userID: 0x%lx 0x%lx\n", titleID, (u64)(userID>>64), (u64)userID);
    }

    if (R_SUCCEEDED(rc)) {
        rc = fsMount_SaveData(&tmpfs, titleID, userID);
        if (R_FAILED(rc)) {
            printf("fsMount_SaveData() failed: 0x%x\n", rc);
            return 0;
        }

    }

    if (R_SUCCEEDED(rc)) {
        ret = fsdevMountDevice("save", tmpfs);
        if (ret==-1) {
            printf("fsdevMountDevice() failed.\n");
            rc = ret;
            return 0;
        }
    }

    return 1;

}

