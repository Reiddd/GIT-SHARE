import java.util.*; // Calendar
import java.text.*; // DateFormat

public class CalendarEg {
    public static void main(String[] args) {
        try {
            DateFormat dateFormat   = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
            String     formatedDate = dateFormat.format(new Date());
            System.out.println(formatedDate);

            Calendar calendar       = Calendar.getInstance();
            Calendar.setTime(new Date());
            System.out.println("Year         : " +  calendar.get(Calendar.YEAR)        );
            System.out.println("Month        : " + (calendar.get(Calendar.MONTH) + 1)  );
            System.out.println("Minute       : " +  calendar.get(Calendar.MINUTE)      );
            System.out.println("Day of year  : " +  calendar.get(Calendar.DAY_OF_YEAR) );
            System.out.println("Day of month : " +  calendar.get(Calendar.DAY_OF_MONTH));
            System.out.println("\n");

            calendar.add(Calendar.HOUR_OF_DAY, 3);
            formatedDate = (new SimpleDateFormat("yyyy-MM-dd HH:mm:ss")).format(calendar.getTime());
            System.out.println("Time after 3 hours : " + calendar.getTime() + "    " + formatedDate);
        }
    }
}