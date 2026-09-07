## EasyGPS固件

项目结构、启动流程、数据流、作者信息证据和二次开发方法见：

- [项目学习指南](docs/项目学习指南.md)

快速构建：

```powershell
python -m platformio run
```

#### LVGL配置说明

工程已经在`platformio.ini`中通过`LV_CONF_INCLUDE_SIMPLE`和`-I lib`配置了`lib/lv_conf.h`，无需手动复制配置文件。
