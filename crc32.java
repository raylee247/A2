import java.sql.Timestamp;
import java.util.Calendar;
import java.util.Random;
import java.util.zip.CRC32;
import java.util.zip.Checksum;
public class crc32 {

    public static String getCRC32(String key) {
        byte[] bytes = key.getBytes();
        Checksum checksum = new CRC32();
        checksum.update(bytes, 0, bytes.length);
        return String.valueOf(checksum.getValue());
    }

    //credit to Mister Smith for getRandomHexString
    //http://stackoverflow.com/questions/14622622/generating-a-random-hex-string-of-length-50-in-java-me-j2me
    private static String getRandomHexString(int numchars) {
        Random r = new Random();
        StringBuffer sb = new StringBuffer();
        while (sb.length() < numchars) {
            sb.append(Integer.toHexString(r.nextInt()));
        }

        return sb.toString().substring(0, numchars);
    }

    public static void main(String[] args) {
        String x, y;
        
        long start_timer = System.currentTimeMillis();

        do {
            x = getRandomHexString(32);
            y = "ce4dc2f59b65e0e65b09dbb1bc31f770";
            if (getCRC32(y).equals(getCRC32(y)))
                break;
        } while (true);

        long end_timer = System.currentTimeMillis();

        Calendar calendar = Calendar.getInstance();

        System.out.println(x);
        System.out.println(y);
        System.out.println((end_timer - start_timer) + " ms");

    }
}
