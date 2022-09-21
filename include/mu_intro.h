#pragma once

#include <types.h>
#include <st/st_melee.h>
#include <mu/mu_file_io_handle.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <mu/mu_object.h>

struct scriptEntry
{
    int id;
    int length;
};
struct fighter
{
    int charId;
    int displayId;
};

struct muObjectFlags
{
    char *node;
    char flags[4];
};

const int maxMode = 2;
enum modeType
{
    standard = 0x0,
    teams = 0x1,
    breakTheTargets = 0x2
};
enum displayType
{
    standardFighter = 0x0,
    doubleFighter = 0x1,
    giantFighter = 0x2,
    metalFighter = 0x3
};

const int totalEnemies = 3;
const int totalAllies = 2;

class muIntroTask : public gfTask
{
protected:
    // 0x40
    nw4r::g3d::ResFile resfiles[10];
    char paddingagain[0x1C];
    // 0x60
    MuObject *muObjects[10];
    // 0xAC
    int progression;
    modeType mode;
    int enemyCount;
    int allyCount;
    fighter enemies[totalEnemies];
    fighter allies[totalAllies];
    // 0xE4
    int commonFilePre;
    muFileIOHandle *files[8];
    //// 0xE8
    // gfFileIOHandle commonFile;
    //// 0xEC
    // char _spacer2[0x10];
    //// 0xFC
    // gfFileIOHandle miniFile;
    //// 0x100
    // char _spacer3[0x8];

    //  0x108
    char soundScriptStarted;
    char _soundScriptStarted[0x3];
    // 0x10C
    scriptEntry script[0x10];
    // 0x18C
    int scriptCount;
    int scriptCurrent;

public:
    muIntroTask();
    static muIntroTask *create();

    void dispEnemy();
    void createObjResFile();
    void getEnemyResFileName(char *str1, char *str2, char *str3, int fighterId, int fighterDisplayType);
    void getStageSetting();
    bool isLoadFinished();
    void makeSoundScript();
    void createCharModel();
    void loadCharModel();
    void createMuObjects(muObjectFlags data[], int num, nw4r::g3d::ResFile *resFile);
    // personal ease of use code
    inline void addScriptEntry(int ID, int length);
    virtual void processDefault();
    virtual ~muIntroTask();
};
