package me.xbh.lib.core.java.utils

import java.security.MessageDigest

/**
 * <p>
 * 描述： Md5 工具类
 * </p>
 * 创建日期：2017年11月22日.
 * @author wenbin.zhou@ehking.com
 * @version 1.0
 */
class Md5Util {

    companion object {
        /**
         * source.getBytes(utf-8)
         *
         * @param source 字符串
         * @return 返回md5串
         */
        @Throws(Exception::class)
        fun getMD5(source: String): String {
            val md = MessageDigest.getInstance("MD5")
            return toHexStr(md.digest(source.toByteArray(charset("UTF-8"))))
        }

        /**
         * 将二进制转换成16进制
         *
         * @param buf
         * @return
         */
        private fun toHexStr(buf: ByteArray): String {
            val hexString = StringBuffer()
            buf.forEach {
                var plainText = Integer.toHexString(0xff and it.toInt())
                if (plainText.length < 2)
                    plainText = "0$plainText"
                hexString.append(plainText)
            }
            return hexString.toString()
        }
    }
}