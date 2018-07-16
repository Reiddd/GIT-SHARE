package com.shiyanlou.demo.helloworld;

public class HelloWorld {
    private String name;

    public void setName(String name) {
        this.name = name;
    }

    public void printHello() {
        System.out.println("The first spring 3: Hello" + name);
    }
}
