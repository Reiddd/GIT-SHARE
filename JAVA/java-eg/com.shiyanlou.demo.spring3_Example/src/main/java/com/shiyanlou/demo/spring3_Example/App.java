package com.shiyanlou.demo.spring3_Example;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import com.shiyanlou.demo.helloworld.HelloWorld;
import com.shiyanlou.demo.loosely_coupled.OutputHelper;

public class App {
    private static ApplicationContext context;

    public static void main(String[] args) {
        context = new ClassPathXmlApplicationContext(new String[] { "SpringBeans.xml", "Spring-Output.xml" });

        HelloWorld obj1 = (HelloWorld)context.getBean("helloBean");
        obj1.printHello();

        // --------------

        OutputHelper obj2 = (OutputHelper)context.getBean("OutputHelper");
        obj2.generateOutput();
    }
}
