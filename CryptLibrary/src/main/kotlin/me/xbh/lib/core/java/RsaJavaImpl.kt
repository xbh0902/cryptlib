package me.xbh.lib.core.java

import me.xbh.lib.core.cxx.RsaImpl
import me.xbh.lib.core.java.utils.RsaUtil

/**
 * <p>
 * 描述： 加密和解密使用java api 实现。
 * </p>
 * 创建日期：2017年11月22日.
 * @author wenbin.zhou@ehking.com
 * @version 1.0
 */
internal class RsaJavaImpl: RsaImpl(){

    override fun encrypt(plain: String, key: String): String = RsaUtil.encryptByPublicKey(plain, key)

    override fun decrypt(cipher: String, key: String): String = RsaUtil.decryptByPublicKey(cipher, key)
}