// version 1
public class Lazy {
    private volatile static Lazy lazy;

    private Lazy() {}

    public static Lazy getInstance() {
        if (lazy == null) {
            synchronized (Lazy.class) {
                if (lazy == null) {
                    lazy = new Lazy();
                } } }

        return lazy;
    }
}

// version 2
/*
    public class Lazy {
        private static InstanceHolder {
            public static final Lazy instance = new Lazy();
        }

        private Lazy() {}

        public static Lazy getInstance() {
            return InstanceHolder.instance;
        }
    }
 */