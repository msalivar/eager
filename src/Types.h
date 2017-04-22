#ifndef TYPES_H_
#define TYPES_H_


enum class EntityType {
	DDG,
	CVN,
	FRIGATE,
	CIGARETTE,
	ALIEN
};

enum class COMMAND_TYPE {
	MOVETO,
	FOLLOW,
	INTERCEPT
};

enum class ASPECT_TYPE {
	PHYSICS,
	RENDERABLE,
	AI,
	NONE
};

#endif /* TYPES_H_ */
