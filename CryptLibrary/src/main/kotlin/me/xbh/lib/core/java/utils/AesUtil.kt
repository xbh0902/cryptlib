package me.xbh.lib.core.java.utils

import android.annotation.SuppressLint
import android.util.Base64
import java.security.Key
import javax.crypto.Cipher
import javax.crypto.spec.SecretKeySpec

/**
 * <p>
 * 描述： Aes ECB模式加密解密
 * </p>
 * 创建日期：2017年11月22日.
 * @author wenbin.zhou@ehking.com
 * @version 1.0
 */
class AesUtil {

    companion object {

        private val ALGORITHM = "AES/ECB/PKCS5Padding"
        private val UTF8 = "UTF-8"

        /**
         * 对字符串进行加密，根据指定的密码
         *
         * @param content 需要加密的字符串
         * @param key     密钥
         * @return 返回加密完成之后的十六进制字符串
         * @throws Exception 如果密钥串`content`不匹配或者密钥`key`不匹配会抛出异常
         */
        @SuppressLint("GetInstance")
        @Throws(Exception::class)
        fun encrypt(content: String, key: String): String {
            val cipher = Cipher.getInstance(ALGORITHM)// 创建密码器
            val byteContent = content.toByteArray(charset(UTF8))
            cipher.init(Cipher.ENCRYPT_MODE, toKey(key.toByteArray(charset(UTF8))))// 初始化
            val result = cipher.doFinal(byteContent)
            return encryptBASE64(result) // 加密
        }

        /**
         * 对字符串进行解密，根据指定的密码
         *
         * @param content 需要加密的字符串
         * @param key     密钥
         * @return 返回解密之后的字符串
         * @throws Exception 如果密钥串`content`不匹配或者密钥`key`不匹配会抛出异常
         */
        @SuppressLint("GetInstance")
        @Throws(Exception::class)
        fun decrypt(content: String, key: String): String {

            val decryptFrom = decryptBASE64(content)
            val cipher = Cipher.getInstance(ALGORITHM)// 创建密码器
            cipher.init(Cipher.DECRYPT_MODE, toKey(key.toByteArray(charset(UTF8))))// 初始化
            val result = cipher.doFinal(decryptFrom)
            return String(result, charset(UTF8))
        }

        @Throws(Exception::class)
        fun encryptBASE64(key: ByteArray): String {
            return Base64.encodeToString(key, Base64.DEFAULT)
        }

        @Throws(Exception::class)
        private fun decryptBASE64(key: String): ByteArray {
            return Base64.decode(key, Base64.DEFAULT)
        }

        @Throws(Exception::class)
        private fun toKey(key: ByteArray): Key {
            return SecretKeySpec(key, ALGORITHM)
        }

    }


}