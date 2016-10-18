<?php global $base_url; ?>
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
<table width="100%" bgcolor="#10AED6" cellpadding="0" cellspacing="0" border="0"
       style="font-family: 'Myriad Pro', sans-serif; color: #555555; padding-top: 20px;">
  <tr>
    <td style="padding: 40px 0 0;">
      <table width="880px" cellpadding="0" cellspacing="0" border="0"
             align="center" bgcolor="#F3F3F3" style="position: relative;">
        <tr align="center" bgcolor="transparent">
          <td colspan="2"
              style="padding: 25px; text-transform: uppercase; color: #ffffff; font-size: 24px; font-weight: bold;">
            <?php print $logo; ?>
          </td>
        </tr>
        <tr align="center" bgcolor="transparent">
          <td colspan="2" style="padding: 0;">
            <img height="260px" width="100%" style="display:block;"
                 src="<?php print $base_url; ?>/sites/all/themes/flight_modern/images/mailticket.jpg">
          </td>
        </tr>
        <tr align="center" bgcolor="transparent">
          <td style="padding: 10px 20px;" colspan="2">
            <?php print $hello; ?>
            <h2
              style="font: bold 28px/1.2 'Miriad Pro';color: #3AD3F9; font-family: Myriad Pro,sans-serif;"><?php print $subject; ?></h2>
            <?php print $text; ?>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td>
      <table bgcolor="#f3f3f3" width="880px" align="center" cellpadding="0"
             cellspacing="0" border="0" style="height: 40px;">
        <tr>
          <td></td>
        </tr>
      </table>
      <table width="880px" align="center" cellpadding="0" cellspacing="0"
             border="0" style="color: transparent; font-size: 16px;">
        <tr>
          <td align="left" style="line-height: 10px; color: #ffffff;">
            <?php print $contacts['address']; ?>
            <p
              style="font: 16px/1.2 'Tahoma'; color: #ffffff; text-decoration: none;">
              <?php print $contacts['emails'][0]; ?>
            </p>
          </td>
          <td align="right" style="line-height: 10px;">
            <?php if (isset($contacts['social_networks'])): ?>
              <a style="font: 16px/1.2 'Tahoma'; color: #ffffff" target="_blank"
                 href="  <?php print reset($contacts['social_networks']); ?>">
                <?php print reset($contacts['social_networks']); ?>
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
        <?php print t('Mob. phone'); ?>:
        <?php $i = 0; ?>
        <?php $count_mobile = count($contacts['mobiles']); ?>
        <?php foreach ($contacts['mobiles'] as $index => $mobile) : ?>
          <?php $i++; ?>
          <?php $format_tel = 'tel:' . str_replace(' ', '', filter_var($mobile, FILTER_SANITIZE_NUMBER_INT)); ?>
          <a style="font-size: 16px; color: #393939; text-decoration: none;"
             target="_blank" href="<?php print $format_tel; ?>">
            <?php print trim($mobile); ?><?php if ($index < $count_mobile - 1) {
              print ',';
            } ?>
          </a>
        <?php endforeach; ?>
      </p>
    </td>
  </tr>
</table>