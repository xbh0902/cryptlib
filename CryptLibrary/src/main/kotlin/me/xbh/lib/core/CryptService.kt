package me.xbh.lib.core

import android.content.Context

/**
 * <p>
 * 描述：使用`CryptService`可以对数据加密，提供安全保障。其中包含MD5、AES、和RSA公钥加密解密
 * </p>
 * 创建日期：2017年11月21日.
 * @author wenbin.zhou@ehking.com
 * @version 1.0
 */
interface CryptService {

    /**
     * 获取RSA公钥
     * @param buildType 构建环境
     *                  dev:1、qa:2、pro:3
     */
    fun getRsaPubKey(buildType: Int): String

    /**
     * 获取一个16位的随机密钥
     */
    fun getAesKey(): String

    /**
     * md5加密
     */
    fun md5(plain: String): String

    /**
     * 获取本地密钥
     */
    fun getAesLocalKey(context: Context): String

    /**
     * 加密
     */
    fun encrypt(plain: String, key: String, type: String): String


    /**
     * 解密
     */
    fun decrypt(cipher: String, key: String, type: String): String

    companion object {
        val AES = "aes"
        val RSA = "rsa"
    }

}