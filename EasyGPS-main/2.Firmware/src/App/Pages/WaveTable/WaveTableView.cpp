#include "WaveTableView.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

/**
 * @brief Create and register the LVGL objects owned by Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void WaveTableView::Create(lv_obj_t *root)
{
/**
 * @brief Create and register the LVGL objects owned by BtnCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnCont_Create(root);

/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnA Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Btn_Create(ui.cont, &ui.btnA, "SystemInfos", ResourcePool::GetImage("start"));
/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnB Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_DRIVE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Btn_Create(ui.cont, &ui.btnB, "Dialplate", LV_SYMBOL_DRIVE);
/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnC Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_SETTINGS Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Btn_Create(ui.cont, &ui.btnC, "Settings", LV_SYMBOL_SETTINGS);
/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnG Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_BLUETOOTH Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Btn_Create(ui.cont, &ui.btnG, "BLEKeyboard", LV_SYMBOL_BLUETOOTH);
/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnD Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Btn_Create(ui.cont, &ui.btnD, "Popcat", ResourcePool::GetImage("menu"));
/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_BELL Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Btn_Create(ui.cont, &ui.btnE, "SmartAssistant", LV_SYMBOL_BELL);
/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnF Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_AUDIO Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Btn_Create(ui.cont, &ui.btnF, "Compass", LV_SYMBOL_AUDIO);

}

/**
 * @brief Delete LVGL objects owned by WaveTableView.
 */
void WaveTableView::Delete()
{
    // if (ui.anim_timeline)
    // {
    //     lv_anim_timeline_del(ui.anim_timeline);
    //     ui.anim_timeline = nullptr;
    // }
}

/**
 * @brief Execute the AppearAnimStart operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param reverse Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void WaveTableView::AppearAnimStart(bool reverse) // 开始开场动画
{
    // lv_anim_timeline_set_reverse(ui.anim_timeline, reverse);
    // lv_anim_timeline_start(ui.anim_timeline);
}

/**
 * @brief Create and register the LVGL objects owned by BtnCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void WaveTableView::BtnCont_Create(lv_obj_t *par) // 按钮容器画布的创建
{
    lv_obj_t *cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0xebdcca), LV_PART_MAIN);
    // lv_obj_set_style_bg_img_src(cont, ResourcePool::GetImage("popcat_open"), LV_PART_MAIN); // 设置背景图片

    lv_obj_set_style_pad_all(cont, 25, LV_PART_MAIN); // 设置每一个item的宽度
    lv_obj_set_style_pad_row(cont, 15, LV_PART_MAIN); // 设置每一个item的间距

    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);       // 设置弹性布局，item竖着排
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);               // 设置画布滚动方向：垂直滚动
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER); // 设置在垂直滚动结束时捕捉子元素的位置：人话：打开菜单第一个item的位置，现在是居中
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_ON); // 设置滚动条是否显示：是

    ui.cont = cont;
}

/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param img_src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void WaveTableView::Btn_Create(lv_obj_t *par, btnCont *cont, const char *name, const void *img_src)
{
    // btn
    lv_obj_t *btn = lv_obj_create(par);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, lv_pct(90), lv_pct(23));
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE); // lv_obj_clear_flag用于清除指定对象的标志位。标志位是用来表示对象状态或特性的一个标记，通过设置或清除标志位可以改变对象的行为或外观。
                                                    // 就是说这里删去原本默认的按钮样式，为下面自定义添加图片做准备
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_style_bg_opa(btn, LV_OPA_70, 0);                // 设置透明度，不透明
    lv_obj_set_style_width(btn, lv_pct(80), LV_STATE_PRESSED); // 设置button按下时的长宽
    lv_obj_set_style_height(btn, lv_pct(20), LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0xf4c7c7), 0);                // 设置按钮默认的颜色
    lv_obj_set_style_bg_color(btn, lv_color_hex(0xda8c90), LV_STATE_PRESSED); // 设置按钮在被按下时的颜色
    lv_obj_set_style_bg_color(btn, lv_color_hex(0xa5c4db), LV_STATE_FOCUSED); // 设置按钮在被聚焦时的颜色
    lv_obj_set_style_radius(btn, 12, 0);                                       // 按钮画圆角

    // lv_obj_set_style_shadow_width(btn, 10, 0);
    // lv_obj_set_style_shadow_ofs_x(btn, 1, 0);
    // lv_obj_set_style_shadow_ofs_y(btn, 1, 0);
    // lv_obj_set_style_shadow_color(btn, lv_color_hex(0x9b92ac), 0);
    // lv_obj_set_style_shadow_spread(btn, 1, 0);
    // lv_obj_set_style_shadow_opa(btn, LV_OPA_80, 0);

    // img
    lv_obj_t *img = lv_img_create(btn);
    lv_img_set_src(img, img_src); // 设置item上的图标
    lv_obj_align(img, LV_ALIGN_LEFT_MID, 10, 0); // 设置图标位置

    // label
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, name);
    lv_obj_set_style_text_color(label, lv_color_hex(0x888888), LV_STATE_DEFAULT);
    lv_obj_align_to(label, img, LV_ALIGN_OUT_RIGHT_MID, 20, 0);

    // anim
/**
 * @brief Own and retain the tran state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static lv_style_transition_dsc_t tran;                                                      // lv_style_transition_dsc_t用于描述样式过渡的属性。这个数据结构用于定义样式过渡的动画效果，包括过渡的时间、延迟、缓动函数等属性
/**
 * @brief Own and retain the prop state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static const lv_style_prop_t prop[] = {LV_STYLE_WIDTH, LV_STYLE_HEIGHT, LV_STYLE_PROP_INV}; // lv_style_prop_t枚举类型，用于表示样式的属性。这个枚举类型定义了一系列的样式属性，例如背景颜色、边框宽度、文本颜色等
    lv_style_transition_dsc_init(
        &tran,
        prop,
        lv_anim_path_ease_out,
        150,
        0,
        nullptr); 
    lv_obj_set_style_transition(btn, &tran, LV_STATE_PRESSED);
    lv_obj_set_style_transition(btn, &tran, LV_STATE_FOCUSED);

    lv_obj_update_layout(btn); 

    cont->btn = btn;
    cont->img = img;
    cont->label = label;
}
