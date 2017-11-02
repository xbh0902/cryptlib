package me.xbh.lib

/**
 * <p>
 * 描述：加密接口
 * </p>
 * 创建日期：2017年11月02日.
 * @author wenbin.zhou@ehking.com
 * @version 1.0
 */
interface ICrypt {

    fun getKey(obj : Any?): String

    fun encrypt(plain: String, key: String): String

    fun decrypt(cipher: String, key: String): String

}