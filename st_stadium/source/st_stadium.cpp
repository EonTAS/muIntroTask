#include "st_stadium.h"
#include "gr_final.h"
#include <memory.h>
#include <st/st_class_info.h>
#include <gm/gm_global.h>

static stClassInfoImpl<Stages::Final, stStadium> classInfo = stClassInfoImpl<Stages::Final, stStadium>();

stStadium* stStadium::create()
{
    stStadium* stage = new (Heaps::StageInstance) stStadium();
    return stage;
}
bool stStadium::loading()
{
    return true;
}

void stStadium::createObj()
{
    this->testStageParamInit(m_fileData, 0xA);
    this->testStageDataInit(m_fileData, 0x14, 0x70);
    this->addGround(grStadiumVision::create(3, "", "grStadiumAuroraVision"));
    this->addGround(grMadein::create(0x14, "OVDenki", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0x16, "OVTuchi", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0x15, "OVKoori", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0x17, "OVHikou", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0x18, "OVNormal", "", Heaps::StageInstance));
    this->addGround(grMadein::create(4, "", "grStadiumSearchLight", Heaps::StageInstance));
    this->addGround(grMadein::create(0, "", "grStadiumMainBg", Heaps::StageInstance));
    this->addGround(grMadein::create(1, "StgStadium00AshibaL", "grStadiumAshibaL", Heaps::StageInstance));
    this->addGround(grMadein::create(2, "StgStadium00AshibaR", "grStadiumAshibaR", Heaps::StageInstance));
    this->addGround(grMadein::create(5, "StgStadium00Denki", "grStadiumDenki", Heaps::StageInstance));
    this->addGround(grMadein::create(6, "StgStadium00DenkiRing", "grStadiumDenkiRing", Heaps::StageInstance));
    this->addGround(grMadein::create(7, "StgStadium00Koori", "grStadiumKoori", Heaps::StageInstance));
    this->addGround(grMadein::create(8, "StgStadium00Tuchi", "grStadiumTuchi", Heaps::StageInstance));
    this->addGround(grMadein::create(9, "StgStadium00Hikou", "grStadiumHikou", Heaps::StageInstance));
    this->addGround(grMadein::create(10, "Airmd", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0xb, "Dugtrio", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0xc, "Elekible", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0xd, "Fuwante", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0xe, "Hanecco", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0xf, "Jibacoil", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0x10, "Karakara", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0x11, "Yukikaburi", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0x12, "Yukiwarashi", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0x13, "Conveyor", "", Heaps::StageInstance));
    this->addGround(grMadein::create(200, "DenkiAshiba", "", Heaps::StageInstance));
    this->addGround(grMadein::create(0xc9, "KooriAshiba", "", Heaps::StageInstance));
    int groundNum = this->getGroundNum();
    for (int i = 0; i < groundNum; i++) {
        Ground* ground = this->getGround(i);
        ground->startup(this->m_fileData, 0, 0);
        ground->setStageData(this->m_stageData);
    }
    this->createCollision(this->m_fileData, 2, NULL);
    this->createCollision(this->m_fileData, 3, NULL);
    this->createCollision(this->m_fileData, 4, NULL);
    this->createCollision(this->m_fileData, 5, this->getGround(0xd));
    this->createCollision(this->m_fileData, 6, this->getGround(0xe));
    for (int i = 1; i < groundNum; i++) {
        grMadein* ground = static_cast<grMadein*>(this->getGround(i));
        ground->initializeEntity();
    }
    __memfill(&this->m_beltConveyor1Data, 0, sizeof(this->m_beltConveyor1Data));
    this->m_beltConveyor1Data.m_conveyorPos = (Vec3f){-65.0, 0.0, 0.0};
    this->m_beltConveyor1Data.m_speed = 0.7;
    this->m_beltConveyor1Data.m_isRightDirection = false;
    this->m_beltConveyor1Data.m_pos = (Vec2f){0.0, 0.0};
    this->m_beltConveyor1Data.m_range = (Vec2f){75.0, 10.0};
    stTrigger* trigger = g_stTriggerMng->createTrigger(Gimmick_BeltConveyor, -1);
    trigger->setBeltConveyorTrigger(&this->m_beltConveyor1Data);
    this->m_beltConveyor1Trigger = trigger;
    trigger->setAreaSleep(true);

    __memfill(&this->m_beltConveyor2Data, 0, sizeof(this->m_beltConveyor2Data));
    this->m_beltConveyor2Data.m_conveyorPos = (Vec3f){65.0, 0.0, 0.0};
    this->m_beltConveyor2Data.m_speed = 0.7;
    this->m_beltConveyor2Data.m_isRightDirection = true;
    this->m_beltConveyor2Data.m_pos = (Vec2f){0.0, 0.0};
    this->m_beltConveyor2Data.m_range = (Vec2f){75.0, 10.0};
    trigger = g_stTriggerMng->createTrigger(Gimmick_BeltConveyor, -1);
    trigger->setBeltConveyorTrigger(&this->m_beltConveyor2Data);
    this->m_beltConveyor2Trigger = trigger;
    trigger->setAreaSleep(true);

    static_cast<grMadein*>(this->getGround(6))->startEntityAutoLoop();
    static_cast<grMadein*>(this->getGround(7))->startEntityAutoLoop();
    static_cast<grMadein*>(this->getGround(8))->startEntityAutoLoop();
    static_cast<grMadein*>(this->getGround(9))->startEntityAutoLoop();
    this->getGround(0x19)->setEnableCollisionStatus(false);
    this->getGround(0x1a)->setEnableCollisionStatus(false);
    this->getGround(10)->setEnableCollisionStatus(false);
    this->getGround(0xc)->setEnableCollisionStatus(false);
    this->getGround(0xd)->setEnableCollisionStatus(false);
    this->getGround(0xe)->setEnableCollisionStatus(false);

    initCameraParam();
    void* posData = m_fileData->getData(Data_Type_Model, 0x64, 0xfffe);
    if (posData == NULL)
    {
        // if no stgPos model in pac, use defaults
        createStagePositions();
    }
    else
    {
        // stgPosWrapper stgPos = {posData}; // creates wrapper on the stack
        createStagePositions(&posData);
    }

    stStadiumData* stadiumData = static_cast<stStadiumData*>(this->m_stageData);
    this->m_phaseEvent.set(0.0, 0.0);
    this->m_normalEvent.set(stadiumData->m_normalMinFrames, stadiumData->m_normalMaxFrames);
    this->m_typeEvent.set(1200.0, 1800.0);
    this->m_displayEvent.set(600.0, 600.0);
    this->m_displayTransformEvent.set(600.0, 600.0);
    this->m_preTransformEvent.set(300.0, 300.0);
    this->m_transformEvent.set(200.0, 200.0);
    this->m_electricPkmnEvent.set(400.0, 800.0);
    this->m_normalEvent.start();
    this->m_displayEvent.start();

    nw4r::g3d::ResFileData* scnData = static_cast<nw4r::g3d::ResFileData*>(this->m_fileData->getData(Data_Type_Scene, 0, 0xfffe));
    this->registScnAnim(scnData, 0);
    this->initPosPokeTrainer(1, 0);
    this->createObjPokeTrainer(this->m_fileData, 0x65, "PokeTrainer00", this->m_unk, 0x0);
    this->loadStageAttrParam(m_fileData, 0x1E);

    grStadiumVision* stadiumVision = static_cast<grStadiumVision*>(this->getGround(0));
    stadiumVision->m_stadiumType = 4;
    stadiumVision->m_msgBinData = this->m_fileData->getData(Data_Type_Misc, 0x28, 0xfffe);

    this->setDefaultDisplay();
    this->playSeBasic(snd_se_stage_Stadium_02, 0);
}

void stStadium::createObjDetails() {

}

void stStadium::update(float deltaFrame)
{
    if (this->m_normalEvent.isReadyEnd() && !this->m_phaseEvent.isEvent()) {
        switch(this->m_transformTypes[this->m_transformTypeIndex]) {
            case Type_Electric:
                this->m_stadiumTypeGroundIndex = 10;
                break;
            case Type_Ground:
                this->m_stadiumTypeGroundIndex = 13;
                break;
            case Type_Ice:
                this->m_stadiumTypeGroundIndex = 12;
                break;
            case Type_Flying:
                this->m_stadiumTypeGroundIndex = 14;
                break;
            default:
                break;
        }
        this->m_phaseEvent.start();
        this->m_transformTypeIndex++;
        if (this->m_transformTypeIndex > 3) {
            this->prepareNextTransformTypes();
        }
    }

    this->m_normalEvent.update(deltaFrame);
    this->m_phaseEvent.update(deltaFrame);
    this->m_typeEvent.update(deltaFrame);
    this->m_transformEvent.update(deltaFrame);
    this->m_displayTransformEvent.update(deltaFrame);
    this->m_preTransformEvent.update(deltaFrame);
    this->m_displayEvent.update(deltaFrame);
    this->m_electricPkmnEvent.update(deltaFrame);
    if (this->m_displayEvent.isEvent()) {
        int phase = this->m_displayEvent.getPhase();
        if (phase == 1 && this->m_displayEvent.isReadyEnd()) {
            this->setDefaultDisplay();
        }
        if (phase == 0 || (phase == 1 && !this->m_displayEvent.isReadyEnd())) {
            int nextDisplayIndex = randi(2);
            this->m_displayState++;
            this->m_displayEvent.set(600.0, 1200.0);
            if (this->m_displayState > 6) {
                this->m_displayState = 0;
                nextDisplayIndex = 2;
                this->m_displayEvent.set(300.0, 300.0);
            }
            this->setDefaultDisplay();
            this->m_displayEvent.start();
            grStadiumVision* stadiumVision = static_cast<grStadiumVision*>(this->getGround(0));
            switch(nextDisplayIndex) {
                case 0:
                    this->m_targetZoom = randf()*0.9 + 0.6;
                    this->enableVisionScreen();
                    break;
                case 1:
                    stadiumVision->m_messageDisplay = grStadiumVision::MessageDisplay_Overview;
                    stadiumVision->setDisplay(true);
                    if (this->m_currentDisplayIndex != nextDisplayIndex) {
                        this->playSeBasic(snd_se_stage_Stadium_10,0);
                    }
                    break;
                case 2:
                    stadiumVision->m_messageDisplay = grStadiumVision::MessageDisplay_Leader;
                    stadiumVision->setDisplay(true);
                    if (this->m_currentDisplayIndex != nextDisplayIndex) {
                        this->playSeBasic(snd_se_stage_Stadium_10,0);
                    }
                default:
                    break;
            }
            this->m_currentDisplayIndex = nextDisplayIndex;
            this->m_displayEvent.setPhase(1);
        }
    }
    this->updateVisionScreen();
    this->updateSpecialStage(deltaFrame);
    if (this->m_transformEvent.isEvent()) {
        if (this->m_transformEvent.isReadyEnd()) {
            cmRemoveQuake(1);
            this->stopSeBasic(this->m_transformSfxIndex, 2.0);
            this->m_transformSfxIndex = -1;
            this->m_transformEvent.end();
        }
        else {
            cmReqQuake(1, &(Vec3f){0.0, 0.0, 0.0});
        }
    }
    this->updateSymbol(deltaFrame);
}

void stStadium::notifyEventInfoGo() {

}

void stStadium::notifyEventInfoReady() {

}

void stStadium::setVision(u8 index) {
    short numFramesForMessage[20] = {0, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x3c, 0x78, 0xff, 0xff, 0xff, 0xff, 0xff,
                                     0xff, 0x78, 0x78, 0x78, 0x78, 0x78};
    this->setDefaultDisplay();
    grStadiumVision* stadiumVision = static_cast<grStadiumVision*>(this->getGround(0));
    stadiumVision->m_messageDisplay = static_cast<grStadiumVision::MessageDisplay>(index);
    stadiumVision->setDisplay(true);
    this->m_displayEvent.set(numFramesForMessage[index], numFramesForMessage[index]);
    this->m_displayEvent.start();
    this->m_displayEvent.setPhase(1);
}

void stStadium::enableVisionScreen() {
    grStadiumVision* stadiumVision = static_cast<grStadiumVision*>(this->getGround(0));
    stadiumVision->setDisplay(false);
    stadiumVision->setNodeVisibility(1, 0, "AuroraVision", 0, 0);
    stadiumVision->setNodeVisibility(1, 0, "AuroraVision9monitor", 0, 0);
    int playerNumbers[7] = {0, 0, 0, 0, 0, 0, 0};
    int playerCount = 0;
    for (int i = 0; i < 7; i++) {
        Vec3f pos;
        if (this->getPlayerPosition(i, &pos)) {
            playerNumbers[playerCount] = i;
            playerCount++;
        }
    }
    if (this->m_nextPlayerIndex >= playerCount) {
        this->m_nextPlayerIndex = 0;
    }
    this->m_visionScreenState = VisionScreen_Enabled;
    this->m_focusedPlayerNo = playerNumbers[this->m_nextPlayerIndex];
    this->m_nextPlayerIndex++;

    gmGlobalModeMelee* globalModeMelee = g_GameGlobal->m_modeMelee;
    if (globalModeMelee->m_playersInitData[this->m_focusedPlayerNo].m_characterKind == Character_Purin && globalModeMelee->m_playersInitData[this->m_focusedPlayerNo].m_state == 3) {
        globalModeMelee->m_meleeInitData.m_0x7_0 = true;
    }
    else {
        globalModeMelee->m_meleeInitData.m_0x7_0 = false;
    }
}

void stStadium::updateSpecialStage(float deltaFrame) {

}

void stStadium::updateSymbol(float deltaFrame) {

}

void stStadium::updateVisionScreen() {

}

void stStadium::updateVisionScreenPos() {

}

void Ground::setStageData(void* stageData)
{
    this->m_stageData = stageData;
}
void stStadium::startFighterEvent()
{
    return;
}
int stStadium::initializeFighterAttackRatio()
{
    return 0;
}
int stStadium::helperStarWarp()
{
    return 0;
}
bool stStadium::isSimpleBossBattleMode()
{
    return false;
}
bool stStadium::isBossBattleMode()
{
    return false;
}
bool stStadium::isCameraLocked()
{
    return true;
}
void stStadium::notifyTimmingGameStart()
{
    return;
}
float stStadium::getFrameRuleTime()
{
    return this->m_frameRuleTime;
}
void stStadium::setFrameRuleTime(float newTime)
{
    this->m_frameRuleTime = newTime;
}
bool stStadium::isNextStepBgmEqualNowStepBgmFromFlag()
{
    return false;
}
float stStadium::getBgmPlayOffsetFrame()
{
    return BGM_PLAY_OFFSET_FRAME;
}
float stStadium::getBgmVolume()
{
    return BGM_VOLUME;
}
void stStadium::setBgmChange(float unk, u32 unk1, u32 unk2)
{
    this->m_unk2 = unk1;
    this->m_unk3 = unk2;
    this->m_unk4 = unk;
}
void stStadium::getBgmChangeID(u32 unk1, float unk2)
{
    unk1 = this->m_unk3;
    unk2 = this->m_unk4;
}
bool stStadium::isBgmChange()
{
    return this->m_unk2;
}
int stStadium::getBgmOptionID()
{
    return 0;
}
int stStadium::getNowStepBgmID()
{
    return 0;
}
int stStadium::getBgmID()
{
    return 0;
}
int stStadium::getBgmIDOverload()
{
    return 0;
}
void stStadium::appearanceFighterLocal()
{
    return;
}
// TODO
// stubbed because i can't figure out where this is called
int stStadium::getScrollDir(u32 unk1)
{
    return 0;
}
int stStadium::getDefaultLightSetIndex()
{
    return 0x14;
}
stRange* stStadium::getAIRange()
{
    return &this->m_aiRange;
}
bool stStadium::isAdventureStage()
{
    return false;
}
int stStadium::getPokeTrainerDrawLayer()
{
    return 0;
}
float stStadium::getPokeTrainerPositionZ()
{
    return POKETRAINER_Z;
}
void stStadium::getPokeTrainerPointData(int* unk, int unk2)
{
    return;
}
int stStadium::getPokeTrainerPointNum()
{
    return 0;
}
bool stStadium::isReStartSamePoint()
{
    return true;
}
grGimmickWindData2nd* stStadium::getWind2ndOnlyData()
{
    return m_windAreaData2nd;
}
bool stStadium::isBamperVector()
{
    return true;
}

ST_CLASS_INFO;