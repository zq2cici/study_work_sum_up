/**
*低功耗入口
*/
void low_power_enter()
{
	 ///1：IO口配置成低功耗
	 
	 ///2: 关闭MCU外部模块
	 
	 ///3：设置唤醒机制
	 
	 ///4: 设置MCU进入休眠模式
	 
	 ///5：循环等待唤醒，防止唤醒时，软件跑飞
	 while(1){
		 
		 if( fWake_up == OK ){    ///唤醒条件 == 成立
			 low_power_exit();
			 break;
		 }
	 }
}
/**
*低功耗出口
*/
void low_power_exit()
{
	 ///1：恢复IO口配置
	 
	 ///2: 打开相应MCU外部模块
	 
	 ///3：取消唤醒机制
	 
	 ///4：进入正常的工作模式

}
