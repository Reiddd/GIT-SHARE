package test.hibernate.test;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;

import test.hibernate.entity.User;

public class Test {
    public static void main(String[] args) {
        // get the configuration
        Configuration  configuration  = new Configuration().configure();

        // build the SessionFactory based on the Configuration
        @suppressWarnings("deprecation")
        SessionFactory sessionFactory = configuration.buildSessionFactory();

        // open the Session, which is like java.sql.Connection
        Session        session        = sessionFactory.openSession();

        // create and start the transaction
        session.beginTransaction();

        // create an object
        User user = new User();
        user.setId(1);
        user.setUsername("admin");
        user.setPassword("admin");

        // save the object
        session.save(user);

        // commit the transaction
        session.getTransaction().commit();

        session.close();
        sessionFactory.close();
    }
}
