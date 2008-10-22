/*      
   Tsunami for KallistiOS ##version##
        
   scene.h

   (c)2002 Dan Potter

*/

#ifndef __TSUNAMI_DRW_SCENE_H
#define __TSUNAMI_DRW_SCENE_H

#include "../drawable.h"

/**
  Scene provides a container class which you can use as a top-level drawable
  in your scene setup. It doesn't draw anything itself, so its finishedness
  always depends on its sub-drawables.
 */
class Scene : public Drawable {
public:
	Scene() {
		// Scene is always finished itself, because it doesn't draw
		// anything. This will make it check its sub-drawables for
		// finishedness before acquiescing.
		setFinished();
	}
	virtual ~Scene() {
	}
};

#endif	/* __TSUNAMI_DRW_SCENE_H */

