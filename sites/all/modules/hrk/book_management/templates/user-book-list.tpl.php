<?php
global $language;
global $user;
$l_prefix = ($language->language == 'en') ? 'en' : 'ru';
currency_include('convert');
$currency = strtoupper(currency_get_active_currency());
?>

<div id="account" class="<?php empty($bf) && empty($bh) ? print 'orders-empty' : null ?>">
    <div class="container">
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 filter_account">
            <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12">
                <span><?php print t('Display:') ?></span>
                <div id="switcher">
                    <input type="button" value="<?php print t('Flights') ?>" class="active" data-type=".flight-row"><input type="button" value="<?php print t('Hotels') ?>" class="no_active" data-type=".hotel-row">
                </div>
            </div>
            <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12">
                <span><?php print t('Booking status:') ?></span>
                <div class="select_style filtering">
                    <select>
                        <option data-filter="all" value="all"><?php print t('All');?></option>
                        <option data-filter=".user-booking" value="1"><?php print t('Booked');?></option>
                        <option data-filter=".user-paid" value="2"><?php print t('Paid');?></option>
                        <option data-filter=".user-cancelled" value="3"><?php print t('Canceled');?></option>
                    </select>
                </div>
            </div>
            <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12">
                <span><?php print t('Sort') ?>:</span>
                <div class="select_style ordering">
                    <select>
                        <option data-sort="created:desc" value="default"><?php print t('Creation Date (desc.)');?></option>
                        <option data-sort="created:asc"><?php print t('Creation Date (asc.)');?></option>
                    </select>
                </div>
            </div>
        </div>
        <?php if (!empty($bf)): ?>

            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 table_account user-table user-flights">
                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 tr_account_header">
                    <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 td_account"><?php print t('Order') ?></div>
                    <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><?php print t('Direction') ?></div>
                    <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><?php print t('Departure date') ?></div>
                    <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><?php print t('Price') ?></div>
                    <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><?php print t('Status') ?></div>
                    <div class="col-lg-1 col-md-1 col-sm-1 col-xs-12 td_account"><?php print t('Show more') ?></div>
                </div>

                <div class="user-table-body-flights">
                    <?php foreach ($bf as $book): ?>
                        <?php $book = (object)$book;?>
                        <?php $book_info = ($book->is_ticket && !$book->is_cancel) ? $book->data['ticket'] : $book->data['book']; ?>
                        <?php $book_info = (object)$book_info;
                        $first_flight = (object)$book_info->flights[0][0][0];
                        $depart_info = $book_info->codes['airports'][$first_flight->departure_airport];
                        $arrival_info = $book_info->codes['airports'][$first_flight->arrival_airport];
                        ?>
                        <?php $book_class = ($book->is_ticket)? 'user-paid':'user-booking';?>
                        <?php $book_class = ($book->is_cancel)? 'user-cancelled':$book_class;?>
                        <?php
                        $flight_data = array();
                        $flight_data[] = 'data-created="' . $book->created . '"';
                        $flight_data[] = 'data-expire="' . $book->expire . '"';

                        ?>

                        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 tr_account user-table-body flight-row mix <?php print $book_class;?>" <?php print implode(' ', $flight_data); ?>>
                            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 td_account"><strong><?php print $book_info->passenger['ADT'][0]['first_name'] . ' ' . $book_info->passenger['ADT'][0]['last_name'];?></strong><br>№ <?php print t('reservation') ?> <?php print $book->cid ;?><br><!--1 взрослый--></div>
                            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><a><?php print $depart_info['city']['name_' . $l_prefix]; ?> - <?php print $arrival_info['city']['name_' . $l_prefix]; ?></a></div>
                            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><i class="glyphicon glyphicon-time"></i><?php print format_date($first_flight->departure, 'custom', 'd F Y | H:i') ?></div>
                            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><span class="price"><strong><?php print Currency::init()->price_html($book_info->price['fare'][$currency]);?></strong></span></div>
                            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account">
                                <?php if(!$book->is_ticket && !$book->is_cancel):?>
                                    <?php print t('Booked '); ?><?php print '(';?><?php print ($book->tid)?$book->tid:$book->cid;?><?php print ')';?>
                                    <?php if(!$book->is_ticket && !$book->is_cancel):?>
                                        <?php print t('Reservation expires');?>
                                        <?php print format_date($book->expire,$type = 'medium', $format = 'j M');?>
                                        <?php print date('H-i',$book->expire);?>
                                    <?php endif;?>
                                <?php else:?>
                                    <?php if ($book->is_cancel): ?>
                                        <?php print t('Canceled '); ?>
                                    <?php else: ?>
                                        <span class="book-paid"><?php print t('Paid '); ?></span>
                                    <?php endif; ?>
                                <?php endif;?>
                            </div>
                            <div class="col-lg-1 col-md-1 col-sm-1 col-xs-12 td_account"><a target="_blank" href="<?php print url('flights/book/'.$book->bid);?>" class="more-user dot">...</a></div>
                        </div>
                    <?php endforeach;?>
                </div>
            </div>
        <?php else: ?>

            <div class="no-orders col-lg-12 col-md-12 col-sm-12 col-xs-12 table_account user-table user-flights">
                <div class="content">
                    <h2><?php print t('Welcome to your personal account!') ?></h2>
                    <p><?php print t('When you book a flight or a hotel the information about your purchase will be here.') ?></p>
                    <p><?php print t('Make your first order!') ?></p>
                    <div class="buttons">
                        <a href="/<?php print $GLOBALS['language']->language; ?>" class="button button_flight"><?php print t('Choose flight') ?></a>
                        <a href="<?php print drupal_lookup_path('alias','node/40', $GLOBALS['language']->language);?>" class="button button_hotel"><?php print t('Book hotel') ?></a>
                    </div>
                </div>
            </div>

        <?php endif; ?>

        <?php if(!empty($bh)):?>
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 table_account user-table user-hotels">
                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 tr_account_header">
                    <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 td_account"><?php print t('Hotel') ?></div>
                    <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><?php print t('Rooms') ?></div>
                    <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><?php print t('Check-In Date') ?></div>
                    <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><?php print t('Check-Out Date') ?></div>
                    <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><?php print t('Status') ?></div>
                    <div class="col-lg-1 col-md-1 col-sm-1 col-xs-12 td_account"><?php print t('Show more') ?></div>
                </div>

                <div class="user-table-body-hotels">
                    <?php foreach ($bh as $book):?>
                        <?php $book = (object)$book;?>
                        <?php $hotel = (object)$book->data;?>
                        <?php $_sh_params = (object)$book->data['_sh_params'];?>
                        <?php $book_class = ($book->is_paid)? 'user-paid':'user-booking';?>
                        <?php $book_class = ($book->is_cancel)? 'user-cancelled':$book_class;?>
                        <?php
                        $hotel_data = array();
                        $hotel_data[] = 'data-created="' . $book->created . '"';
                        $hotel_data[] = 'data-expire="' . $book->expire . '"';
                        ?>

                        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 tr_account user-table-body hotel-row mix <?php print $book_class;?>" <?php print implode(' ', $hotel_data); ?>>
                            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 td_account"><strong><?php print $hotel->name;?></strong> <br> <?php print $book->orid.'.'.$book->seid;?></div>
                            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><?php print count($hotel->package['rooms']);?></div>
                            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><i class="glyphicon glyphicon-time"></i><?php print format_date($_sh_params->check_in,'medium','d F Y | D');?></div>
                            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account"><i class="glyphicon glyphicon-time"></i><?php print format_date($_sh_params->check_out,'medium','d F Y | D');?> </div>
                            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 td_account">
                                <?php if(!$book->is_paid && !$book->is_cancel):?>
                                    <?php print t('Booked '); ?><?php print '(';?><?php print $book->orid.'.'.$book->seid;?><?php print ')';?>
                                    <?php print t('Reservation expires');?> <?php print format_date($book->expire,$type = 'medium', $format = 'j M');?>
                                    <?php print date('H-i',$book->expire);?>
                                <?php else:?>
                                    <?php if ($book->is_cancel): ?>
                                        <?php print t('Canceled '); ?>
                                    <?php else: ?>
                                        <span class="book-paid"><?php print t('Paid '); ?></span>
                                    <?php endif; ?>
                                <?php endif;?>
                            </div>
                            <div class="col-lg-1 col-md-1 col-sm-1 col-xs-12 td_account"><a target="_blank" href="<?php print url('hotels/book/'.$book->bid);?>" class="more-user dot">...</a></div>
                        </div>
                    <?php endforeach;?>
                </div>
            </div>
        <?php else:?>
            <div class="no-orders col-lg-12 col-md-12 col-sm-12 col-xs-12 table_account user-table user-hotels">
                <div class="content">
                    <h2><?php print t('Welcome to your personal account!') ?></h2>
                    <p><?php print t('When you book a flight or a hotel the information about your purchase will be here.') ?></p>
                    <p><?php print t('Make your first order!') ?></p>
                    <div class="buttons">
                        <a href="/<?php print $GLOBALS['language']->language; ?>" class="button button_flight"><?php print t('Choose flight') ?></a>
                        <a href="<?php print drupal_lookup_path('alias','node/40', $GLOBALS['language']->language);?>" class="button button_hotel"><?php print t('Book hotel') ?></a>
                    </div>
                </div>
            </div>
        <?php endif;?>
    </div>
</div>