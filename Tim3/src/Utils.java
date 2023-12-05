public class Utils {
    public static boolean isNumeric(String value){
        try {
            Long.parseLong(value);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

}
