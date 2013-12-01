/*
 * Constant.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: itamar
 */

#include "Constant.h"

const Constant *Constant::True = new Constant(&Word::True, &Type::Bool);
const Constant *Constant::False = new Constant(&Word::False, &Type::Bool);
