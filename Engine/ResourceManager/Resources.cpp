#include "Resources.h"

Resources& Resources::get() {
	static Resources resource;
	return resource;
}

Resources::Resources() : 
	fontHolder("Fonts", "ttf"), 
	textureHolder("Images", "png"), 
	soundHolder("Music", "wav")
{}