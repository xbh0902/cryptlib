package me.xbh.lib.core.cxx

import android.content.Context
import me.xbh.lib.core.ICrypt
import me.xbh.lib.core.CryptService
import java.util.*


/**
 * <p>
 * 描述：使用`CryptServiceImpl`可以对数据加密，提供安全保障。其中包含MD5、AES、和RSA公钥加密解密
 * </p>
 * 创建日期：2017年11月02日.
 * @author wenbin.zhou@ehking.com
 * @version 1.0
 */
internal class CryptServiceImpl : CryptService {

    private val objs = HashMap<String, ICrypt>()

    init {
        objs.put(CryptService.AES, AesImpl())
        objs.put(CryptService.RSA, RsaImpl())
    }

    /**
     * 获取RSA公钥
     * @param buildType 构建环境
     *                  dev:1、qa:2、pro:3
     */
    override fun getRsaPubKey(buildType: Int): String = getElement(CryptService.RSA).getKey(buildType)

    /**
     * 获取一个16位的随机密钥
     */
    override fun getAesKey(): String = getElement(CryptService.AES).getKey(null)

    /**
     * md5加密
     */
    override fun md5(plain: String): String = Md5().digest(plain)

    /**
     * 获取本地密钥
     */
    override fun getAesLocalKey(context: Context) = getElement(CryptService.AES).getKey(context)

    /**
     * 加密
     */
    override fun encrypt(plain: String, key: String, type: String): String {
        val crypt = getElement(type)
        return crypt.encrypt(plain, key)
    }


    /**
     * 解密
     */
    override fun decrypt(cipher: String, key: String,type: String): String {
        val crypt = getElement(type)
        return crypt.decrypt(cipher, key)
    }

    private fun getElement(type: String): ICrypt {
        return objs[type] as ICrypt
    }
}