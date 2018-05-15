/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/**
 * c++ friendly interface for
 * */
//
// Created by furture on 2018/5/15.
//

#ifndef WSON_PARSER_H
#define WSON_PARSER_H

#include "wson.h"

#include <vector>
#include <string>

typedef std::basic_string<uint16_t, std::char_traits<uint16_t>, std::allocator<uint16_t> > u16string;


class wson_parser {

public:
    wson_parser(const char* data);
    wson_parser(const char* data, int length);
    ~wson_parser();

    inline bool hasNext(){
        return wson_has_next(this->buffer);
    }

    inline uint8_t nextType(){
        if(buffer->data && wson_has_next(buffer)){
            return  wson_next_type(buffer);
        }
        return WSON_NULL_TYPE;
    }

    inline void backType(){
        if(buffer && buffer->position > 0){
            buffer->position--;
        }
    }


    inline bool isMap(uint8_t type){
        return type == WSON_MAP_TYPE;
    }

    inline bool isArray(uint8_t type){
        return type == WSON_ARRAY_TYPE;
    }

    inline bool isString(uint8_t type){
        return type == WSON_STRING_TYPE
               || type == WSON_NUMBER_BIG_INT_TYPE
               || type == WSON_NUMBER_BIG_DECIMAL_TYPE;
    }

    inline bool isBool(uint8_t type){
        return type == WSON_BOOLEAN_TYPE_FALSE || type == WSON_BOOLEAN_TYPE_TRUE;
    }

    inline bool isNumber(uint8_t type){
        return type == WSON_NUMBER_INT_TYPE
               || type == WSON_NUMBER_FLOAT_TYPE
               || type == WSON_NUMBER_LONG_TYPE
               || type == WSON_NUMBER_DOUBLE_TYPE;
    }

    /**
     * return map size
     * */
    inline  int  nextMapSize(){
        return wson_next_uint(buffer);
    }

    /**
     * return array size
     * */
    inline  int  nextArraySize(){
        return wson_next_uint(buffer);
    }

    /**
     * auto convert  utf-16 string number to utf-8 string
     * */
    std::string nextMapKeyUTF8();

    /**
     * auto convert object or number to string
     * */
    std::string nextStringUTF8(uint8_t type);

    /**
     * return number value, if type is string convert to number
     * */
    double nextNumber(uint8_t type);

    /** return bool value */
    bool  nextBool(uint8_t type);

    /**
     * skip current value type
     * */
    void skipValue(uint8_t type);


private:
    wson_buffer* buffer;
    void toJSONtring(std::string &builder);
};




#endif //WEEX_PROJECT_WSON_PARSER_H
