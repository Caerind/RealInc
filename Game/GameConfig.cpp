#include "GameConfig.hpp"

std::string GameConfig::configFilename = "../Assets/Data/config.ini";
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
	setS("win-title", "Real Inc.");
	setI("win-width", 1024);
	setI("win-height", 768);
	setI("aabb", 0);
	setI("event1-var", 3000);
	setI("event2-var", 2500);
	setI("event3-var", 2500);
	setI("event4-var", 5000);
	setI("event5-var", 1000);
	setI("event6-var", 3000);
	setI("player-collision", 120);
	setI("player-life", 300);
	setI("player-armor", 300);
	setI("player-speed", 250);
	setI("player-boost", 1000);
	setI("player-regen", 2);
	setI("trader-collision", 120);
	setI("trader-life", 500);
	setI("trader-armor", 400);
	setI("trader-speed", 100);
	setI("trader-capacity", 20);
	setI("enemy1-collision", 120);
	setI("enemy1-life", 100);
	setI("enemy1-armor", 50);
	setI("enemy1-speed", 300);
	setI("enemy2-collision", 120);
	setI("enemy2-life", 50);
	setI("enemy2-armor", 100);
	setI("enemy2-speed", 250);
	setI("enemy3-collision", 150);
	setI("enemy3-life", 200);
	setI("enemy3-armor", 100);
	setI("enemy3-speed", 200);
	setI("planetgen-len-a", 400);
	setI("planetgen-len-b", 2000);
	setI("boost-consume", 5);
	setI("enemy-stop", 400);
	setI("enemy-vision", 700);
	setI("enemy-cooldown", 1);
	setI("spawner-len", 3000);
	setI("spawner-cooldown", 10);
	setI("proj-speed", 800);
	setI("proj-damage", 25);
	setI("proj-damagecrit", 10);
	setI("money-start", 200);
	setI("ast-life - 0", 120);
	setI("ast-life - 1", 300);
	setI("ast-damage", 20);
	setI("ast-amount", 24);
	setF("ast-cooldown", 0.3f);
}

ConfigWindow::ConfigWindow(F32 x, F32 y, F32 w, F32 h)
	: oe::ImGuiWindow("ConfigWindow", x, y, w, h)
{
}

void ConfigWindow::draw()
{
	if (isVisible())
	{
		ImGuiWindow::Begin(10, 10, 300, 200);

		ImGui::BeginChild("Settings");

		if (ImGui::Button("AABB"))
		{
			if (GameConfig::getU("aabb") == 1)
			{
				GameConfig::setU("aabb", 0);
			}
			else
			{
				GameConfig::setU("aabb", 1);
			}
		}

		ImGui::Separator();

		F32 var;

		#define SETTING(str, min, max) \
		var = GameConfig::getF(str); \
		ImGui::SliderFloat(str, &var, min, max); \
		GameConfig::setF(str, var);

		SETTING("event1-var", 500, 5000);
		SETTING("event2-var", 500, 5000);
		SETTING("event3-var", 500, 5000);
		SETTING("event4-var", 500, 5000);
		SETTING("event5-var", 500, 5000);
		SETTING("event6-var", 500, 5000);

		ImGui::Separator();

		SETTING("player-life", 50, 1000);
		SETTING("player-armor", 50, 1000);
		SETTING("player-speed", 100, 500);
		SETTING("player-boost", 500, 5000);
		SETTING("player-regen", 0.5f, 4.0f);
		SETTING("trader-life", 50, 1000);
		SETTING("trader-armor", 50, 1000);
		SETTING("trader-speed", 100, 500);

		ImGui::Separator();

		SETTING("enemy1-life", 50, 1000);
		SETTING("enemy1-armor", 50, 1000);
		SETTING("enemy1-speed", 100, 500);
		SETTING("enemy2-life", 50, 1000);
		SETTING("enemy2-armor", 50, 1000);
		SETTING("enemy2-speed", 100, 500);
		SETTING("enemy3-life", 50, 1000);
		SETTING("enemy3-armor", 50, 1000);
		SETTING("enemy3-speed", 100, 500);

		ImGui::Separator();

		SETTING("planetgen-len-a", 500, 5000);
		SETTING("planetgen-len-b", 500, 5000);
		SETTING("proj-speed", 500, 2000);
		SETTING("proj-damage", 10, 100);
		SETTING("proj-damagecrit", 5, 50);

		#undef SETTING

		ImGui::EndChild();

		ImGui::End();
	}
}
