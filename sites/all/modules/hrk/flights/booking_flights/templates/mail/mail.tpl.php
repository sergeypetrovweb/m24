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
                  <img height="260px" width="100%" style="display:block;" src="<?php print $base_url;?>/sites/all/themes/flight_modern/images/mailbg.jpg">
                </td>
            </tr>
            <tr align="center" bgcolor="transparent">
                <td style="padding: 10px 20px;" colspan="2">
                    <h2 style="font: bold 28px/1.2 'Miriad Pro';color: #3AD3F9; font-family: Myriad Pro,sans-serif;"><?php print $title;?></h2>
                    <?php if(!empty($expire)):?>
                        <p><?php print t('Tickets must be paid to').' '. $expire;?>.</p>
                          <p style="color: #E94D37; font-style: italic;"><?php print t('Left ');?> <?php print $left_time;?></p>
                    <?php endif;?>
                    <h2 style="font: bold 28px/1.2 'Miriad Pro';color: #3AD3F9; font-family: Myriad Pro,sans-serif;"><?php print $context_title;?> <?php print $context_id;?></h2>
                    <h3 style="font: 24px/1.2 'Miriad Pro';color: #313B43; font-family: Myriad Pro,sans-serif;"><!--Нет значения--></h3>
                    <?php if(!empty($book_link_title)):?>
                      <a href="<?php print $base_url.'/'.$GLOBALS['language']->language;?>/flights/book/<?php print $bid;?>" style="padding: 10px 20px; text-decoration: none; background: #E94D37; color: #ffffff;"><?php print t($book_link_title);?></a>
                      <?php //print $book_link;?>
                    <?php endif;?>
                </td>
            </tr>
            <tr align="left" bgcolor="#eff1f3">
                <td colspan="2">
                    <table cellpadding="0" cellspacing="0" border="0" >
                        <tr>
                            <td style="text-transform: uppercase; color: #0FADD5; font-size: 16px; padding: 30px 20px 5px;">
                                <?php print t('passengers');?>
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
            <tr>
                <td colspan="3" style="padding: 5px 20px 15px;">
                    <table cellpadding="0" cellspacing="0" border="0" style="width: 100%;">
                      <thead style="width: 100%;">
                      <tr style="font: 16px 'Tahoma';color: #595959; background: #ffffff; border-radius: 3px; padding: 0; ">
                        <td style="padding: 15px 20px;">№</td>
                        <td style="padding: 15px 20px;"><?php print t('Last name');?></td>
                        <td style="padding: 15px 20px;"><?php print t('First name');?></td>
                        <td style="padding: 15px 20px;"><?php print t('Birthday');?></td>
                        <td style="padding: 15px 20px;"><?php print t('Passport number');?></td>
                      </tr>
                    </thead>
                  <tbody  style="width: 100%; font: 16px 'Tahoma';color: #595959; background: #ffffff; border-radius: 3px; padding: 0;">
                  <tr style="background: #F3F3F3; height: 10px;"><td></td><td></td><td></td><td></td><td></td></tr>
                    <?php $index = 0;?>
                    <?php foreach ($passengers as $type=>$type_passengers):?>
                      <?php foreach ($type_passengers as $passenger):?>
                        <?php $passenger = (object)$passenger; $index++?>
                        <tr>
                          <td style="padding: 15px 20px;"><?php print $index;?>.</td>
                          <td style="padding: 15px 20px;"><?php print ($passenger->sex);?>. <?php print $passenger->last_name;?></td>
                          <td style="padding: 15px 20px;"><?php print $passenger->first_name;?></td>
                          <td style="padding: 15px 20px;"><?php print date('d.m.Y',strtotime($passenger->birthday));?></td>
                          <td style="padding: 15px 20px;"><?php print $passenger->document['id'];?></td>
                        </tr>
                      <?php endforeach;?>
                    <?php endforeach;?>
                    </tbody>
                  </table>
                </td>
            </tr>
        </table>
    </td>
</tr>
<?php foreach ($flights as $ref_num => $direction_flights):?>
    <?php $color = (($ref_num+1)%2)?'#ffffff':'#eff1f3';?>
    <?php foreach ($direction_flights as $dir => $unit_flights) : ?>
        <?php $direction_class = ($direction_type == 'round_trip' && $dir == 1) ? 'from' : 'to' ?>
        <tr>
            <td>
                <table width="880px" cellpadding="0" cellspacing="0" border="0" align="center" bgcolor="#f3f3f3">
                    <?php foreach ($unit_flights as $index => $flight) : ?>
                        <?php $flight = (object)$flight; ?>
                        <?php $next_flight = isset($unit_flights[$index + 1]) ? (object)$unit_flights[$index + 1] : array(); ?>
                        <?php $depart_info = $codes['airports'][$flight->departure_airport]; ?>
                        <?php $arrival_info = $codes['airports'][$flight->arrival_airport]; ?>
                        <tr align="left">
                            <td style="padding: 0 20px;">
                              <table cellpadding="0" cellspacing="0" border="0" style="width: 100%;">
                                <tr style="text-align: center;">
                                  <td style="width: 33%"> </td>
                                  <td><p style="font-weight: bold; font-size: 18px; text-align: center;"><?php print $depart_info['city']['name_' . $l_prefix]; ?> - <?php print $arrival_info['city']['name_' . $l_prefix]; ?></p></td>
                                  <td style="font-size: 16px; text-align: right; color: #E94D37;">
                                    <?php print '(' . format_interval($flight->elapsed_time) . ')'; ?>
                                  </td>
                                </tr>
                                </table>
                                <div style="padding: 0 10px;">
                                  <p style="font-size: 18px;">
                                    <?php print $depart_info['city']['name_' . $l_prefix]; ?>,
                                    <span style="font-size: 14px; font-style: italic;"><?php print $depart_info['country']['name_' . $l_prefix]; ?></span>
                                    <span style="margin: 0 10px"><img style="display:inline-block;" height="11px" width="16px" src="<?php print $base_url;?>/sites/all/themes/flight_modern/images/mailarrow.png"></span>
                                    <?php print $arrival_info['city']['name_' . $l_prefix]; ?>,
                                    <span style="font-size: 14px; font-style: italic;"><?php print $arrival_info['country']['name_' . $l_prefix]; ?></span>
                                  </p>
                                    <p style="font-size: 18px;">
                                      <?php print t('departure'); ?>: <?php print format_date($flight->departure, 'medium', 'j F'); ?>, <?php print format_date($flight->departure, 'medium', 'l'); ?>
                                    </p>
                                </div>
                            </td>
                        </tr>
                        <tr bgcolor="#eff1f3">
                            <td colspan="2" style="padding: 0 20px;">
                                <table cellpadding="0" cellspacing="0" border="0" style="width: 100%">
                                  <thead style="width: 100%">
                                    <tr style="font: 16px 'Tahoma';color: #595959; background: #ffffff; border-radius: 3px; padding: 0;">
                                     <td style="padding: 15px 20px;"><?php print t('Departure'); ?></td>
                                     <td style="padding: 15px 20px;"><?php print t('Airport'); ?></td>
                                     <td style="padding: 15px 20px;"><?php print t('Arrival'); ?></td>
                                     <td style="padding: 15px 20px;"><?php print t('Airport'); ?></td>
                                     <td style="padding: 15px 20px;"><?php print t('Flight'); ?></td>
                                     <td style="padding: 15px 20px;"><?php print t('Airplane'); ?></td>
                                    </tr>
                                  </thead>
                                  <tbody style="width: 100%">
                                  <tr style="background: #F3F3F3; height: 10px;"><td></td><td></td><td></td><td></td><td></td><td></td></tr>
                                    <tr style="font: 16px 'Tahoma';color: #595959; background: #ffffff; border-radius: 3px; padding: 0;">
                                      <td style="padding: 15px 20px;"><?php print date('H:i', $flight->departure); ?> <span><?php print format_date($flight->departure, 'medium', 'jM'); ?></span></td>
                                      <td style="padding: 15px 20px;"><?php print $depart_info['name_' . $l_prefix]; ?></td>
                                      <td style="padding: 15px 20px;"><?php print date('H:i', $flight->arrival); ?> <span style="font-size: 16px;"><?php print format_date($flight->arrival, 'medium', 'jM'); ?></span></td>
                                      <td style="padding: 15px 20px;"><?php print $arrival_info['name_' . $l_prefix]; ?></td>
                                      <td style="padding: 15px 20px;"><?php print $flight->flight_number; ?></td>
                                      <td style="padding: 15px 20px;"><?php print $codes['airplanes'][$flight->equipment]['name']; ?></td>
                                  </tr>
                                  </tbody>
                                </table>
                            </td>
                        </tr>
                        <?php if ($next_flight): ?>
                            <tr align="left">
                                <td style="padding-top: 15px; padding-left: 20px; padding-bottom: 26px; font-size: 16px;" colspan="2">
                                    <?php print t('Arrival'); ?>:
                                    <span>
                                        <?php print format_date($flight->arrival, 'medium', 'j F'); ?>
                                    </span>
                                    <span style="color: #E94D37; margin-left: 15px;">
                                        <?php print t('Transfer through'); ?>
                                        <?php $next_flight_date = date_create(date('Y-m-d H:i:s', $next_flight->departure)); ?>
                                        <?php $flight_date = date_create(date('Y-m-d H:i:s', $flight->arrival)); ?>
                                        <?php $transfer_time = date_diff($next_flight_date, $flight_date); ?>
                                        <?php print format_interval(($transfer_time->h * 3600) + ($transfer_time->i * 60)); ?>
                                    </span>
                                </td>
                            </tr>
                        <?php endif;?>
                    <?php endforeach;?>
                 </table>
            </td>
        </tr>
    <?php endforeach;?>
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