package me.xbh.cryptlib.ui;

import java.security.SecureRandom;

/**
 * 类<code>RandomUtils</code>是一个随机数工具类。
 *
 * @author wenbin.zhou@ehking.com
 * @version 1.0 2017/05/31 10:35
 * @since JDK1.7
 */
public class RandomUtils {

    /**
     * 生成固定长度数字字符串
     *
     * @param length 长度
     * @return 返回长度为<code>length</code>的数字字符串
     */
    public static String generateDigit(int length) {
        if (length < 1) {
            return "";
        }

        StringBuilder sb = new StringBuilder();
        SecureRandom rand = new SecureRandom();
        for (int i = 0; i < length; i++) {
            sb.append(rand.nextInt(10));
        }
        return sb.toString();
    }

    /**
     * 生成固定长度字母字符串
     *
     * @param length 长度
     * @return 返回相应长度为<code>length</code>的字母字符串
     */
    public static String generateAlphaAndDigit(int length) {
        if (length < 1) {
            return "";
        }
        StringBuilder sb = new StringBuilder();
        SecureRandom rand = new SecureRandom();//随机用以下三个随机生成器
        SecureRandom randdata = new SecureRandom();
        int data = 0;
        for (int i = 0; i < length; i++) {
            int index = rand.nextInt(3);
            //目的是随机选择生成数字，大小写字母
            switch (index) {
                case 0:
                    data = randdata.nextInt(10);//仅仅会生成0~9
                    sb.append(data);
                    break;
                case 1:
                    data = randdata.nextInt(26) + 65;//保证只会产生65~90之间的整数
                    sb.append((char) data);
                    break;
                case 2:
                    data = randdata.nextInt(26) + 97;//保证只会产生97~122之间的整数
                    sb.append((char) data);
                    break;
            }
        }
        return sb.toString();
    }
}
