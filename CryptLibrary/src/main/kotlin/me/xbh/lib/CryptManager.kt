package me.xbh.lib

import android.content.Context
import me.xbh.lib.bean.Type
import me.xbh.lib.impl.AesImpl
import me.xbh.lib.impl.RsaImpl
import java.util.*


/**
 * Created by lulu on 17-9-27.
 */
object CryptManager{

    private val objs = HashMap<String, ICrypt>()

    init {
        System.loadLibrary("ehkingCrypt2")
        objs.put(Type.AES.name, AesImpl())
        objs.put(Type.RSA.name, RsaImpl())
    }

    /**
     * 获取RSA公钥
     * @param buildType 构建环境
     *                  dev:1、qa:2、pro:3
     */
    fun getRsaPubKey(buildType: Int): String = getElement(Type.RSA).getKey(buildType)

    /**
     * 获取一个16位的随机密钥
     */
    fun getAesKey(): String = getElement(Type.AES).getKey(null)

    /**
     * md5加密
     */
    fun md5(plain: String): String = Md5.digest(plain)

    /**
     * 获取本地密钥
     */
    fun getAesLocalKey(context: Context) = getElement(Type.AES).getKey(context)

    /**
     * 加密
     */
    fun encrypt(type: Type, plain: String, key: String): String{
        val crypt = getElement(type)
        return crypt.encrypt(plain, key)
    }


    /**
     * 解密
     */
    fun decrypt(type: Type, cipher: String, key: String): String{
        val crypt = getElement(type)
        return crypt.decrypt(cipher, key)
    }

    private fun getElement(type: Type): ICrypt {
        return objs[type.name] as ICrypt
    }
}