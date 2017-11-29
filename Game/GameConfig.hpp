#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP

#include "../Engine/System/ParserIni.hpp"

class GameConfig
{
	public:
		static std::string getS(const std::string& index);
		static I32 getI(const std::string& index);
		static F32 getF(const std::string& index);
		static U32 getU(const std::string& index);
		template <typename T>
		static T get(const std::string& index);

		static void setS(const std::string& index, const std::string& value);
		static void setI(const std::string& index, I32 value);
		static void setF(const std::string& index, F32 value);
		static void setU(const std::string& index, U32 value);
		template <typename T>
		static void set(const std::string& index, const T& value);

		static bool loadFromFile(const std::string& filename);
		static bool saveToFile(const std::string& filename);
		static void loadFromInternal();

		static oe::ParserIni mIni;
};

#endif // GAMECONFIG_HPP

template<typename T>
inline T GameConfig::get(const std::string & index)
{
	return oe::fromString<T>(getS(index));
}

template<typename T>
inline void GameConfig::set(const std::string & index, const T & value)
{
	setS(index, oe::toString(value));
}
