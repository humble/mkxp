/*
** plane-binding.cpp
**
** This file is part of mkxp.
**
** Copyright (C) 2013 Jonas Kulla <Nyocurio@gmail.com>
**
** mkxp is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** mkxp is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with mkxp.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "plane.h"
#include "disposable-binding.h"
#include "viewportelement-binding.h"
#include "binding-util.h"
#include "binding-types.h"

DEF_TYPE(Plane);

MRB_METHOD(planeInitialize)
{
	Plane *p = viewportElementInitialize<Plane>(mrb, self);

	setPrivateData(mrb, self, p, PlaneType);

	p->setColor(new Color);
	p->setTone(new Tone);

	wrapNilProperty(mrb, self, CSbitmap);
	wrapProperty(mrb, self, p->getColor(), CScolor, ColorType);
	wrapProperty(mrb, self, p->getTone(), CStone, ToneType);

	return self;
}

#define DISP_CLASS_NAME "plane"

DEF_PROP_OBJ(Plane, Bitmap, Bitmap, CSbitmap)
DEF_PROP_OBJ(Plane, Color, Color, CScolor)
DEF_PROP_OBJ(Plane, Tone, Tone, CStone)

DEF_PROP_I(Plane, OX)
DEF_PROP_I(Plane, OY)
DEF_PROP_I(Plane, Opacity)
DEF_PROP_I(Plane, BlendType)

DEF_PROP_F(Plane, ZoomX)
DEF_PROP_F(Plane, ZoomY)


void
planeBindingInit(mrb_state *mrb)
{
	RClass *klass = mrb_define_class(mrb, "Plane", 0);

	disposableBindingInit<Plane>     (mrb, klass);
	viewportElementBindingInit<Plane>(mrb, klass);

	mrb_define_method(mrb, klass, "initialize", planeInitialize, MRB_ARGS_OPT(1));

	INIT_PROP_BIND( Plane, Bitmap,    "bitmap"     );
	INIT_PROP_BIND( Plane, OX,        "ox"         );
	INIT_PROP_BIND( Plane, OY,        "oy"         );
	INIT_PROP_BIND( Plane, ZoomX,     "zoom_x"     );
	INIT_PROP_BIND( Plane, ZoomY,     "zoom_y"     );
	INIT_PROP_BIND( Plane, Opacity,   "opacity"    );
	INIT_PROP_BIND( Plane, BlendType, "blend_type" );
	INIT_PROP_BIND( Plane, Color,     "color"      );
	INIT_PROP_BIND( Plane, Tone,      "tone"       );

	mrb_define_method(mrb, klass, "inspect", inspectObject, MRB_ARGS_NONE());
}
