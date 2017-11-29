#include "GameConfig.hpp"

oe::ParserIni GameConfig::mIni;

std::string GameConfig::getS(const std::string & index)
{
	return mIni.get(index);
}

I32 GameConfig::getI(const std::string & index)
{
	return get<I32>(index);
}

F32 GameConfig::getF(const std::string & index)
{
	return get<F32>(index);
}

U32 GameConfig::getU(const std::string & index)
{
	return get<U32>(index);
}

void GameConfig::setS(const std::string & index, const std::string & value)
{
	mIni.set(value, index);
}

void GameConfig::setI(const std::string & index, I32 value)
{
	set<I32>(index, value);
}

void GameConfig::setF(const std::string & index, F32 value)
{
	set<F32>(index, value);
}

void GameConfig::setU(const std::string & index, U32 value)
{
	set<U32>(index, value);
}

bool GameConfig::loadFromFile(const std::string & filename)
{
	return mIni.loadFromFile(filename);
}

bool GameConfig::saveToFile(const std::string & filename)
{
	return mIni.saveToFile(filename);
}

void GameConfig::loadFromInternal()
{

}
