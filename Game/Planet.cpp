#include "Planet.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Math/Random.hpp"

Planet::Planet(oe::EntityManager& manager, const oe::Vector2& previousPlanetPos, U32 planetsReached)
	: oe::Entity(manager)
	, mPlanet(*this)
{
	mScale = oe::Random::get<F32>(2.f, 5.f);
	mRadius = 50.0f;
	mColor = getRandomColor();
	mName = getRandomName();

	setPosition(previousPlanetPos + oe::Vector2::polarVector(oe::Random::getDev<F32>(0.f, 45.f), getLength(planetsReached)));
	setPositionZ(-100);

	mPlanet.setTexture(GameSingleton::mPlanetTexture);
	mPlanet.setPosition(-mRadius * mScale, -mRadius * mScale);
	mPlanet.setColor(mColor);
	mPlanet.setScale(mScale, mScale);

	U32 imp = oe::Random::get<U32>(0, 4);
	mPrices[0] = (imp == 0) ? oe::Random::get<U32>(6, 8) : oe::Random::get<U32>(10, 22);
	mPrices[1] = mPrices[0] - ((imp == 0) ? oe::Random::get<U32>(1, 2) : oe::Random::get<U32>(2, 5));
	mPrices[2] = (imp == 1) ? oe::Random::get<U32>(6, 8) : oe::Random::get<U32>(10, 22);
	mPrices[3] = mPrices[2] - ((imp == 1) ? oe::Random::get<U32>(1, 2) : oe::Random::get<U32>(2, 5));
	mPrices[4] = (imp == 2) ? oe::Random::get<U32>(6, 8) : oe::Random::get<U32>(10, 22);
	mPrices[5] = mPrices[4] - ((imp == 2) ? oe::Random::get<U32>(1, 2) : oe::Random::get<U32>(2, 5));

	mDiscount = imp;
}

void Planet::update(oe::Time dt)
{
	if (GameConfig::getU("aabb") == 1)
		oe::DebugDraw::drawPoint(getPosition());
}

F32 Planet::getScale() const
{
	return mScale;
}

F32 Planet::getRadius() const
{
	return mRadius;
}

F32 Planet::getFinalRadius() const
{
	return mScale * mRadius;
}

const oe::Color& Planet::getColor() const
{
	return mColor;
}

const std::string & Planet::getName() const
{
	return mName;
}

U32 Planet::getPrices(U32 index) const
{
	return mPrices[index];
}

U32 Planet::getDiscount() const
{
	return mDiscount;
}

F32 Planet::getLength(U32 reached)
{
	if (reached == 0)
	{
		return 0.0f;
	}
	return GameConfig::getF("planetgen-len-b") + reached * GameConfig::getF("planetgen-len-a");
}

oe::Color Planet::getRandomColor()
{
	oe::Color c = oe::Color((U8)oe::Random::get<U32>(0, 255), (U8)oe::Random::get<U32>(0, 255), (U8)oe::Random::get<U32>(0, 255));
	if (c.r < 32)
	{
		c.r = 32;
	}
	if (c.g < 32)
	{
		c.g = 32;
	}
	if (c.b < 32)
	{
		c.b = 32;
	}
	return c;
}

std::string Planet::getRandomName()
{
	static std::vector<std::string> names = {
		"Ank Morpork",
		"Arkham",
		"Arthedain",
		"Altair",
		"Aldebaran",
		"Barad Dur",
		"Balmorra",
		"Cassiopeia",
		"Cirith Ungol",
		"Dunwich",
		"Dag",
		"Eriador",
		"Esgaroth",
		"Eldir",
		"Fulla",
		"Fangorn",
		"Fornax",
		"Cthulhu Land",
		"Gondor",
		"Grus",
		"Gnaa",
		"Hoder",
		"Hoth",
		"Ibaar",
		"Irmin",
		"Isengard",
		"Insmouth",
		"Jarnsaxa",
		"Jakku",
		"Khazad Dum",
		"Krasir",
		"Klatch",
		"Klatooine",
		"Lothal",
		"Loki",
		"Lothlorien",
		"Minas Morgul",
		"Mordor",
		"Moria",
		"Mygeeto",
		"Naboo",
		"Nixus",
		"Nott",
		"Narfi",
		"Numenor",
		"Nurnen",
		"Osgiliath",
		"Oiomure",
		"Odin",
		"Obroa Skai",
		"Orion",
		"Pantora",
		"Pelargir",
		"Pelori",
		"Quell",
		"Rohan",
		"Romenna",
		"Ran",
		"Raxus Prime",
		"Ralltiir",
		"Selonia",
		"Saleucami",
		"Sigyn",
		"Sorontil",
		"Sagitta",
		"Taurus",
		"Tol Eressea",
		"Tol Morwen",
		"Thor",
		"Tatooine",
		"Umbarra",
		"Ull",
		"Utumno",
		"Ursa",
		"Volans",
		"Valmar",
		"Valinor",
		"Vidar",
		"Vanqor",
		"Wynkahthu",
		"Wolde",
		"Xantapoulos",
		"Ygg",
		"Ylesia",
		"Ziost"
	};

	if (names.empty())
	{
		return "Unknown planet";
	}

	U32 id = oe::Random::get<U32>(0, names.size() - 1);

	std::string temp = names[id];

	names.erase(names.begin() + id);

	return temp;
}
