#include "StateParser.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "TextureID.h"

StateParser::StateParser()
{
}

StateParser::~StateParser()
{
}

bool StateParser::ParseState(const char* stateFile, std::string stateID)
{
    // create the XML document
    TiXmlDocument xmlDoc;
    // load the state file
    if (!xmlDoc.LoadFile(stateFile))
    {
        std::cerr << xmlDoc.ErrorDesc() << "\n";
        return false;
    }

    // get the root element
    TiXmlElement* pRoot = xmlDoc.RootElement();

    // pre declare the states root node
    TiXmlElement* pStateRoot = 0;

    // get this states root node and assign it to pStateRoot
    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == stateID)
        {
            pStateRoot = e;
        }
    }

    // pre declare the texture root
    TiXmlElement* pTextureRoot = 0;

    // get the root of the texture elements
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("TEXTURES"))
        {
            pTextureRoot = e;
        }
    }
    // now parse the textures
    ParseTextures(pTextureRoot);

	// sounds
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("SOUNDS"))
        {
            pTextureRoot = e;
        }
    }
    ParseSounds(pTextureRoot);

    return true;
}

void StateParser::ParseTextures(TiXmlElement* pStateRoot)
{
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        bool tmp;
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute = e->Attribute("ID");
        TextureManager::Instance().load(filenameAttribute, idAttribute);

    	if (idAttribute == TextureID::ENEMY_HUMAN)
    	{
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(64, 48);
            int startCul = 0;
            int startRow = 0;

            animation.name = TextureID::ENEMY_HUMAN_IDLE;
            startCul = 0;
            startRow = 1;
            for (int i = 0; i < 2; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();


            animation.name = TextureID::ENEMY_HUMAN_ATTACK;
            startCul = 0;
            startRow = 3;
            for (int i = 0; i < 4; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();

            animation.name = TextureID::ENEMY_HUMAN_FALL;
            startCul = 0;
            startRow = 0;
            for (int i = 0; i < 1; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();

            animation.name = TextureID::ENEMY_HUMAN_JUMP;
            startCul = 2;
            startRow = 0;
            for (int i = 0; i < 1; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();

            animation.name = TextureID::ENEMY_HUMAN_HIT;
            startCul = 5;
            startRow = 3;
            for (int i = 0; i < 4; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();

            animation.name = TextureID::ENEMY_HUMAN_RUN;
            startCul = 0;
            startRow = 2;
            for (int i = 0; i < 4; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();
    	}
    }
}

void StateParser::ParseSounds(TiXmlElement* pStateRoot)
{
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute = e->Attribute("ID");
        std::string soundTypeString = e->Attribute("soundtype");
        const SoundType soundType = soundTypeString == "bgm" ? SoundType::SOUND_MUSIC : SoundType::SOUND_SFX;

        SoundManager::Instance().load(filenameAttribute, idAttribute, soundType);
    }
}
