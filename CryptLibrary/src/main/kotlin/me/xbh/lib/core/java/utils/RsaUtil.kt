package me.xbh.lib.core.java.utils

import android.util.Base64
import java.security.Key
import java.security.KeyFactory
import java.security.spec.X509EncodedKeySpec
import javax.crypto.Cipher

/**
 * <p>
 * 描述：Rsa 公钥加密解密工具类
 * </p>
 * 创建日期：2017年11月22日.
 * @author wenbin.zhou@ehking.com
 * @version 1.0
 */
class RsaUtil private constructor() {

    companion object {

        private val RSA_ALGORITHM = "RSA/ECB/PKCS1Padding"
        private val RSA = "RSA"
        /**
         * 加密方法
         *
         * @param source    源数据
         * @param publicKey 公钥
         * @return 返回加密后的字符串
         * @throws Exception 如果加密失败抛出该异常
         */
        @Throws(Exception::class)
        fun encryptByPublicKey(source: String, publicKey: String): String {
            //换取密钥
            val key = getPublicKeyByString(publicKey)
            //得到Cipher对象来实现对源数据的RSA加密
            val cipher = Cipher.getInstance(RSA_ALGORITHM)
            cipher.init(Cipher.ENCRYPT_MODE, key)
            val b = source.toByteArray()
            //执行加密操作
            val b1 = cipher.doFinal(b)
            return Base64.encodeToString(b1, Base64.NO_WRAP)
        }

        /**
         * 解密算法
         *
         * @param cryptograph 数据源
         * @param publishKey  公钥
         * @return 返回解密后的数据
         * @throws Exception 如果解密失败抛出该异常
         */
        @Throws(Exception::class)
        fun decryptByPublicKey(cryptograph: String, publishKey: String): String {
            //换取密钥
            val key = getPublicKeyByString(publishKey)
            //得到Cipher对象对已用公钥加密的数据进行RSA解密
            val cipher = Cipher.getInstance(RSA_ALGORITHM)
            cipher.init(Cipher.DECRYPT_MODE, key)
            val b1 = Base64.decode(cryptograph.toByteArray(), Base64.DEFAULT)
            //执行解密操作
            val b = cipher.doFinal(b1)
            return String(b)
        }

        // 换取密钥
        private fun getPublicKeyByString(key: String): Key {
            val keyBytes = Base64.decode(key, Base64.DEFAULT)
            val x509EncodedKeySpec = X509EncodedKeySpec(keyBytes)
            val keyFactory = KeyFactory.getInstance(RSA)
            return keyFactory.generatePublic(x509EncodedKeySpec)
        }

    }
}