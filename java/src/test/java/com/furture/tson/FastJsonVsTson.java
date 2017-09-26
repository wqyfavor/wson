package com.furture.tson;

import com.alibaba.fastjson.JSON;
import com.efurture.wson.Wson;
import junit.framework.TestCase;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by 剑白(jianbai.gbj) on 2017/8/16.
 */
public class FastJsonVsTson extends TestCase {



    public void testFastJson(){
        String json = null;
        long start = System.currentTimeMillis();
        for(int i=0; i<10000; i++) {
            Map<String, Object> map = new HashMap<>();
            map.put("name", "hello world");
            map.put("age", 1);
            json = JSON.toJSONString(map);
        }
        long end = System.currentTimeMillis();
        System.out.println("fastjson used " + (end - start));

        start = System.currentTimeMillis();
        for(int i=0; i<10000; i++) {
            JSON.parseObject(json);
        }
        end = System.currentTimeMillis();
        System.out.println("fastjson parse used " + (end - start));
    }



    public void testTson(){
        byte[] data = null;
        long start = System.currentTimeMillis();
        for(int i=0; i<10000; i++) {
            Map<String, Object> map = new HashMap<>();
            map.put("name", "hello world");
            map.put("age", 1);
            data = Wson.toWson(map);
        }
        long end = System.currentTimeMillis();

        System.out.println("wson totson used " + (end - start));

        start = System.currentTimeMillis();
        for(int i=0; i<10000; i++) {
            Wson.parse(data);
        }
        end = System.currentTimeMillis();

        System.out.println("wson parse used " + (end - start));
    }

    public void testSerializable(){
        User user = new User();
        user.name = "中国";
        user.country = "中国";

        long start = System.currentTimeMillis();
        for(int i=0; i<10000; i++) {
           Wson.toWson(user);
        }
        long end = System.currentTimeMillis();
        System.out.println("wson totson used " + (end - start));

        start = System.currentTimeMillis();
        for(int i=0; i<10000; i++) {
            JSON.toJSONString(user);
        }
        end = System.currentTimeMillis();
        System.out.println("json totson used " + (end - start));
    }



}
