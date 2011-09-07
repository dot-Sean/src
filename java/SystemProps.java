import java.util.Properties;

class SystemProps {
    public static void main(String[] args) {
        Properties properties = System.getProperties();
        for (Object key: properties.keySet()) {
            System.out.println(key + ": " + properties.get(key));
        }
    }
}

//        System.getProperties().list(System.out);
//        System.out.println(System.getProperty("sun.boot.class.path"));
