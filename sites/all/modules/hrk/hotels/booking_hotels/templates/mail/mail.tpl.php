<?php global $base_url;?>
<style type="text/css">
  p {
    font: 16px/1.5 "Miriad Pro";
    color: #303B43;
  }

  td {
    padding: 0;
  }

  a {
    font: 16px/1.2 'Tahoma';
    color: #ffffff;
    text-decoration: none;
    border: 0;
  }
</style>

<table width="100%" bgcolor="#10AED6" cellpadding="0" cellspacing="0" border="0" style="font-family: 'Myriad Pro', sans-serif; color: #555555; padding-top: 20px;">
<tr>
  <td style="padding: 40px 0 0;">
    <table width="880px" cellpadding="0" cellspacing="0" border="0" align="center" bgcolor="#F3F3F3" style="position: relative;">
      <tr align="center" bgcolor="transparent">
        <td colspan="2" style="padding: 25px; text-transform: uppercase; color: #ffffff; font-size: 24px; font-weight: bold;">
          <!--                  <p style="float:left;">--><?php //print $airline['name'];?><!--</p>-->
          <?php print $logo;?>
        </td>
      </tr>
      <tr align="center" bgcolor="transparent">
        <td colspan="2" style="padding: 0;">
          <img height="260px" width="100%" style="display:block;" src="<?php print $base_url;?>/sites/all/themes/flight_modern/images/mailhotel.jpg">
        </td>
      </tr>
      <tr align="center" bgcolor="transparent">
        <td style="padding: 10px 20px;" colspan="2">
          <h2 style="font: bold 28px/1.2 'Miriad Pro';color: #3AD3F9; font-family: Myriad Pro,sans-serif;"><?php print $title;?></h2>
          <?php $addition_info = (object)$addition_info;?>
          <?php $format_check_in = format_date($addition_info->check_in, 'medium', 'j F'); ?>
          <?php $format_check_out = format_date($addition_info->check_out, 'medium', 'j F'); ?>
          <p>
            <?php print $addition_info->nights . ' '; ?><?php print format_plural($addition_info->nights, t('night'), t('nights')); ?>
            <?php print t('during the period from @check_in to @check_out', array('@check_in' => $format_check_in, '@check_out' => $format_check_out)); ?>
          </p>
          <?php if(!empty($expire)):?>
            <p><?php print t('Rooms must be paid to').' '. $expire;?></p>
              <p style="color: #E94D37; font-style: italic;"><?php print t('Left ');?> <?php print $left_time;?></p>
          <?php endif;?>
          <?php if(!empty($cancel_id)):?>
            <h2 style="font: bold 28px/1.2 'Miriad Pro';color: #3AD3F9; font-family: Myriad Pro,sans-serif;"><?php print $cancel_title;?> <?php print $cancel_id;?></h2>
          <?php else:?>
            <h2 style="font: bold 28px/1.2 'Miriad Pro';color: #3AD3F9; font-family: Myriad Pro,sans-serif;"><?php print $book_title;?> <?php print $book_id;?></h2>
            <h3 style="font: 24px/1.2 'Miriad Pro';color: #313B43; font-family: Myriad Pro,sans-serif;"><?php print $order_title;?> <?php print $order_id;?></h3>
            <h3 style="font: 24px/1.2 'Miriad Pro';color: #313B43; font-family: Myriad Pro,sans-serif;"><?php print $segment_title;?> <?php print $segment_id;?></h3>
          <?php endif;?>
          <?php if(!empty($book_link_title)):?>
            <a href="<?php print $base_url.'/'.$GLOBALS['language']->language;?>/hotels/book/<?php print $bid;?>" style="padding: 10px 20px; text-decoration: none; background: #E94D37; color: #ffffff;"><?php print t($book_link_title);?></a>
          <?php endif;?>
        </td>
      </tr>
    </table>
  </td>
</tr>
<?php foreach ($rooms as $room):?>
  <?php $room = (object)$room;?>
  <tr>
    <td style="padding: 0 !important;">
      <table width="880px" cellpadding="0" cellspacing="0" border="0" align="center" bgcolor="#f3f3f3">
        <tr align="left">
          <td colspan="2" style="padding: 0 !important;">
            <table>
              <tr>
                <td style="text-transform: uppercase; color: #0FADD5; font-size: 16px; padding: 30px 20px 5px;">
                  <?php print t('Guests');?>
                </td>
              </tr>
            </table>
          </td>
        </tr>
        <tr>
          <td colspan="3" style="padding:0 20px 15px;">
            <table style="width: 100%;">
              <tr style="width: 100%; font: 16px 'Tahoma';color: #595959; background: #ffffff; border-radius: 3px; padding: 0;">
                <td style="padding: 15px 20px;">№</td>
                <td style="padding: 15px 20px;"><?php print t('Last name');?></td>
                <td style="padding: 15px 20px;"><?php print t('First name');?></td>
              </tr>
              <tr style="background: #F3F3F3; height: 10px;"><td></td><td></td><td></td><td></td><td></td></tr>
              <?php if(!empty($room->guests)):?>
                <?php foreach ($room->guests as $guests_bu_type):?>
                  <?php $index = 1;?>
                  <?php foreach ($guests_bu_type as $guest):?>
                    <tr  style="width: 100%; font: 16px 'Tahoma';color: #595959; background: #ffffff; border-radius: 3px; padding: 0;">
                      <td style="padding: 15px 20px;"><?php print $index;?>.</td>
                      <td style="padding: 15px 20px;"><?php print $guest['sex'];?>. <?php print $guest['last_name'];?></td>
                      <td style="padding: 15px 20px;"><?php print $guest['first_name'];?></td>
                    </tr>
                    <?php $index++;?>
                  <?php endforeach;?>
                <?php endforeach;?>
              <?php endif;?>
            </table>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td>
      <table width="880px" cellpadding="0" cellspacing="0" border="0" align="center" bgcolor="#f3f3f3">
        <tr align="left" bgcolor="#ffffff">
<!--          <td style="padding: 20px 0 0 25px;">-->
<!--            --><?php //if(!empty($room->image['src'])):?>
<!--              --><?php //$html_img = theme('imagecache_external', array('path' => $room->image['src'], 'style_name' => 'bh_room_image')); ?>
<!--              --><?php //if ($html_img): ?>
<!--                --><?php //print $html_img; ?>
<!--              --><?php //endif;?>
<!--            --><?php //endif;?>
<!--          </td>-->
          <td style="padding: 10px 20px;">
            <span style="text-transform: uppercase; color: #0FADD5; font-size: 16px; padding: 30px 20px 5px;"><?php print $room->class; ?> <?php print $room->type; ?></span>
            <p style="padding: 0 20px;"><?php print $room->basis; ?></p>
            <p style="padding: 0 20px;"><?php print $room->class; ?></p>
            <p style="padding: 0 20px;"><?php print $room->type; ?></p>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <?php if($room->description):?>
    <tr>
      <td>
        <table width="880px" cellpadding="0" cellspacing="0" border="0" align="center" bgcolor="#f3f3f3">
          <tr align="left" bgcolor="#ffffff">
            <td style="padding: 20px 25px;">
              <span style="color: #205081; font-size: 20px; text-transform: uppercase;"><?php print t('room description');?></span>
              <?php foreach ($room->description as $description):?>
                <p><?php print $description; ?></p>
              <?php endforeach;?>
            </td>
          </tr>
        </table>
      </td>
    </tr>
  <?php endif;?>
<?php endforeach;?>

<tr>
  <td>
    <table bgcolor="#f3f3f3" width="880px" align="center" cellpadding="0" cellspacing="0" border="0" style="height: 40px;">
      <tr><td></td></tr>
    </table>
    <table width="880px" align="center" cellpadding="0" cellspacing="0" border="0"  style="color: transparent; font-size: 16px;">
      <tr>
        <td align="left" style="line-height: 10px; color: #ffffff;">
          <?php print $contacts['address'];?>
          <p style="font: 16px/1.2 'Tahoma'; color: #ffffff; text-decoration: none;">
            <!--                      <a style="font: 16px/1.2 'Tahoma'; color: #ffffff; text-decoration: none;" target="_blank" href="mailto:--><?php //print reset($contacts['emails']);?><!--">-->
            <?php print $contacts['emails'][0];?>
            <!--                        </a>-->
          </p><!--
                    <p>

                    </p>-->
        </td>
        <td align="right" style="line-height: 10px;">
          <?php if (isset($contacts['social_networks'])): ?>
            <a style="font: 16px/1.2 'Tahoma'; color: #ffffff" target="_blank" href="  <?php print reset($contacts['social_networks']);?>">
              <?php print reset($contacts['social_networks']);?>
            </a>
          <?php endif; ?>
        </td>
      </tr>
    </table>
  </td>
</tr>
<tr style="background: #ffffff; text-align: center">
  <td style="font-size: 16px; color: #393939;">
    <p>
      <?php print t('Mob. phone');?>:
      <?php $i = 0;?>
      <?php $count_mobile = count($contacts['mobiles']);?>
      <?php foreach ($contacts['mobiles'] as $index=>$mobile) :?>
        <?php $i++;?>
        <?php $format_tel = 'tel:'.str_replace(' ','',filter_var($mobile, FILTER_SANITIZE_NUMBER_INT));?>
        <a style="font-size: 16px; color: #393939; text-decoration: none;" target="_blank" href="<?php print $format_tel;?>">
          <?php print trim($mobile);?><?php if ($index < $count_mobile - 1) print ',';?>
        </a>
      <?php endforeach;?>
    </p>
  </td>
</tr>
</table>