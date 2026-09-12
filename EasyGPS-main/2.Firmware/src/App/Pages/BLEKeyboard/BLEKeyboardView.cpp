#include "BLEKeyboardView.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

/**
 * @brief Create and register the LVGL objects owned by Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void BLEKeyboardView::Create(lv_obj_t *root)
{
    lv_obj_t *cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0xe9e1e8), LV_PART_MAIN);
    lv_obj_set_align(cont, LV_ALIGN_CENTER);

    lv_obj_set_style_pad_hor(cont, 10, LV_PART_MAIN); // 设置每一个item的宽度
    lv_obj_set_style_pad_row(cont, 30, LV_PART_MAIN);      // 设置每一个item的间距
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);       // 设置弹性布局，item竖着排
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);               // 设置画布滚动方向：垂直滚动
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER); // 设置在垂直滚动结束时捕捉子元素的位置：人话：打开菜单第一个item的位置，现在是居中
    // lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    ui.cont = cont;

/**
 * @brief Create and register the LVGL objects owned by BtnCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param xb9aacc Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    ui.musicCtrlCont.cont = BtnCont_Create(ui.cont, 0xb9aacc);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnPrevTrack Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_PREV Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.musicCtrlCont.cont, &ui.musicCtrlCont.btnPrevTrack, "Prev", LV_SYMBOL_PREV);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnPause Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_PAUSE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.musicCtrlCont.cont, &ui.musicCtrlCont.btnPause, "Pause", LV_SYMBOL_PAUSE);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnNextTrack Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_NEXT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.musicCtrlCont.cont, &ui.musicCtrlCont.btnNextTrack, "Next", LV_SYMBOL_NEXT);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnVolumeDown Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_VOLUME_MID Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.musicCtrlCont.cont, &ui.musicCtrlCont.btnVolumeDown, "Vol<", LV_SYMBOL_VOLUME_MID);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnMute Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_MUTE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.musicCtrlCont.cont, &ui.musicCtrlCont.btnMute, "Mute", LV_SYMBOL_MUTE);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnVolumeUp Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_VOLUME_MAX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.musicCtrlCont.cont, &ui.musicCtrlCont.btnVolumeUp, "Vol>", LV_SYMBOL_VOLUME_MAX);
    // BtnKeyboard_Create(ui.musicCtrlCont.cont, &ui.musicCtrlCont.btnVolumeDown, "Vol<", ResourcePool::GetImage("start"));

/**
 * @brief Create and register the LVGL objects owned by BtnCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param xf4a460 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    ui.directionCtrlCont.cont = BtnCont_Create(ui.cont, 0xf4a460);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnCopy Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_COPY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.directionCtrlCont.cont, &ui.directionCtrlCont.btnCopy, "Copy", LV_SYMBOL_COPY);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnDirUp Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_UP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.directionCtrlCont.cont, &ui.directionCtrlCont.btnDirUp, "Up", LV_SYMBOL_UP);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnCut Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_CUT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.directionCtrlCont.cont, &ui.directionCtrlCont.btnCut, "Cut", LV_SYMBOL_CUT);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnPaste Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_PASTE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.directionCtrlCont.cont, &ui.directionCtrlCont.btnPaste, "Paste", LV_SYMBOL_PASTE);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnDirDown Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_DOWN Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.directionCtrlCont.cont, &ui.directionCtrlCont.btnDirDown, "Down", LV_SYMBOL_DOWN);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnWithdraw Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_LOOP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.directionCtrlCont.cont, &ui.directionCtrlCont.btnWithdraw, "Back", LV_SYMBOL_LOOP);

/**
 * @brief Create and register the LVGL objects owned by BtnCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param xcfdcae Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    ui.mouseMoveCtrlCont.cont = BtnCont_Create(ui.cont, 0xcfdcae);
/**
 * @brief Create and register the LVGL objects owned by MouseCircle_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    ui.mouseMoveCtrlCont.btnMouse = MouseCircle_Create(ui.mouseMoveCtrlCont.cont);

/**
 * @brief Create and register the LVGL objects owned by BtnCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param xcfdcae Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    ui.mouseClickCtrlCont.cont = BtnCont_Create(ui.cont, 0xcfdcae);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnBack Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_PREV Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.mouseClickCtrlCont.cont, &ui.mouseClickCtrlCont.btnBack, "Back", LV_SYMBOL_PREV);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnPageUp Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_UP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.mouseClickCtrlCont.cont, &ui.mouseClickCtrlCont.btnPageUp, "Up", LV_SYMBOL_UP);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnForward Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_NEXT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.mouseClickCtrlCont.cont, &ui.mouseClickCtrlCont.btnForward, "Forward", LV_SYMBOL_NEXT);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnLeft Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_LEFT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.mouseClickCtrlCont.cont, &ui.mouseClickCtrlCont.btnLeft, "Left", LV_SYMBOL_LEFT);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnPageDown Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_DOWN Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.mouseClickCtrlCont.cont, &ui.mouseClickCtrlCont.btnPageDown, "Down", LV_SYMBOL_DOWN);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param btnRight Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_SYMBOL_RIGHT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnKeyboard_Create(ui.mouseClickCtrlCont.cont, &ui.mouseClickCtrlCont.btnRight, "Right", LV_SYMBOL_RIGHT);
}

/**
 * @brief Delete LVGL objects owned by BLEKeyboardView.
 */
void BLEKeyboardView::Delete()
{
    if (ui.anim_timeline)
    {
        lv_anim_timeline_del(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
}

/**
 * @brief Execute the AppearAnimStart operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param reverse Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void BLEKeyboardView::AppearAnimStart(bool reverse) // 开始开场动画
{
    lv_anim_timeline_set_reverse(ui.anim_timeline, reverse);
    lv_anim_timeline_start(ui.anim_timeline);
}

// 按钮容器画布的创建
/**
 * @brief Create and register the LVGL objects owned by BtnCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param c Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
lv_obj_t *BLEKeyboardView::BtnCont_Create(lv_obj_t *par, uint32_t c)
{
    lv_obj_t *cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, lv_pct(100), lv_pct(75));
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(cont, lv_color_hex(c), LV_PART_MAIN);
    lv_obj_set_style_radius(cont, 30, LV_PART_MAIN);
    lv_obj_align(cont, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_style_pad_all(cont, 0, LV_PART_MAIN);  // 设置每一个item的宽度
    lv_obj_set_style_pad_row(cont, 10, LV_PART_MAIN); // 设置每一个item的间距

    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(
        cont,
        LV_FLEX_ALIGN_SPACE_EVENLY, // 在主轴或交叉轴上平均分配空间，包括首尾
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER);

/**
 * @brief Own and retain the cont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return cont;
}

/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param img_src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void BLEKeyboardView::BtnKeyboard_Create(lv_obj_t *par, btnCont *cont, const char *name, const void *img_src)
{
    // btn
    lv_obj_t *btn = lv_obj_create(par);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, lv_pct(30), 70);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE); // lv_obj_clear_flag用于清除指定对象的标志位。标志位是用来表示对象状态或特性的一个标记，通过设置或清除标志位可以改变对象的行为或外观。
                                                    // 就是说这里删去原本默认的按钮样式，为下面自定义添加图片做准备
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_style_bg_opa(btn, LV_OPA_70, 0);                // 设置透明度，不透明
    lv_obj_set_style_width(btn, lv_pct(25), LV_STATE_PRESSED); // 设置button按下时的长宽
    lv_obj_set_style_height(btn, 55, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0xffc8ca), 0);                // 设置按钮默认的颜色
    lv_obj_set_style_bg_color(btn, lv_color_hex(0xaf97b6), LV_STATE_PRESSED); // 设置按钮在被按下时的颜色
    lv_obj_set_style_bg_color(btn, lv_color_hex(0xd0daff), LV_STATE_FOCUSED); // 设置按钮在被聚焦时的颜色
    lv_obj_set_style_radius(btn, 12, 0);                                      // 按钮画圆角

    // img
    lv_obj_t *img = lv_img_create(btn);
    lv_img_set_src(img, img_src);                // 设置item上的图标
    lv_obj_align(img, LV_ALIGN_LEFT_MID, 10, 0); // 设置图标位置

    // label
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, name);
    lv_obj_align_to(label, img, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xaeac9d), LV_PART_MAIN);

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


/**
 * @brief Create and register the LVGL objects owned by MouseCircle_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
lv_obj_t *BLEKeyboardView::MouseCircle_Create(lv_obj_t *par)
{
    // btn
    lv_obj_t *btn = lv_obj_create(par);
    lv_obj_remove_style_all(btn);
    lv_obj_set_size(btn, 100, 100);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE); // lv_obj_clear_flag用于清除指定对象的标志位。标志位是用来表示对象状态或特性的一个标记，通过设置或清除标志位可以改变对象的行为或外观。

    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, LV_PART_MAIN); // 设置透明度，不透明
    lv_obj_set_style_width(btn, 85, LV_STATE_PRESSED);        // 设置button按下时的长宽
    lv_obj_set_style_height(btn, 85, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0xabc0a0), LV_PART_MAIN);     // 设置按钮默认的颜色
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x9bb090), LV_STATE_PRESSED); // 设置按钮在被按下时的颜色
    lv_obj_set_style_radius(btn, LV_RADIUS_CIRCLE, 0);                        // 按钮画圆角

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

    lv_obj_update_layout(btn);

/**
 * @brief Own and retain the btn state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return btn;
}
