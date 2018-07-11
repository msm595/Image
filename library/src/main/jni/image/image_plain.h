/*
 * Copyright 2016 Hippo Seven
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// Created by Hippo on 5/3/2016.
//

#ifndef IMAGE_IMAGE_PLAIN_H
#define IMAGE_IMAGE_PLAIN_H


#include "static_image.h"

bool plain_init(ImageLibrary* library);

StaticImage* plain_create(uint32_t width, uint32_t height, const uint8_t* buffer);


#endif // IMAGE_IMAGE_PLAIN_H
