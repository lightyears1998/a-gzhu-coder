import java.awt.*;
import java.security.*;


/**
 * 生成颜色的工具类
 */
public class Colorful {

    /**
     * 为一个字符串生成它的颜色。
     */
    static Color getColorFromString(String str) {
        int r = 0, g = 0, b = 0;
        try {
            byte[] bytes = MessageDigest.getInstance("MD2").digest(str.getBytes());
            r = Byte.toUnsignedInt(bytes[0]);
            g = Byte.toUnsignedInt(bytes[1]);
            b = Byte.toUnsignedInt(bytes[2]);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return new Color(r, g, b);     
    }
}
