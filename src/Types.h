#ifndef TYPES_H_
#define TYPES_H_


enum class EntityType {
	BLUETANK,
	BLUETURRET,
	REDTANK,
	REDTURRET,
	BULLET,
	NONE,
	WALL
};

enum class ASPECT_TYPE {
	PHYSICS,
	RENDERABLE,
	AI,
	NONE
};

enum class EntityState {
	ALIVE,
	DESTROY,
	DEAD,
	NONE
};

enum class STATE {
	SPLASH,
	MAIN_MENU,
	GAMEPLAY,
	WIN_SCREEN
};
#endif /* TYPES_H_ */
