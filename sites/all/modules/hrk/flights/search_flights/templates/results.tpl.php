<?php
$path = drupal_get_path('theme', 'flight_modern');
currency_include('convert');

global $user;
global $language;
$l_prefix = ($language->language == 'en') ? 'en' : 'ru';
$currency = strtoupper(currency_get_active_currency());
$currency_prefix = currency_get_prefix();
$combinations_index = array();
//Индексы для сортировок и мин. мах. значений фильтров.
$transfer_index = array();
$time_in_air_index = array();
$price_sort = array();
$i = 0;

$currency_help = Currency::init();

$air_codes = array();

if ($calendar) {
	echo('<div class="flights-calendar-popup" style="display:none">');
  echo('<div class="popup-bg flights-calendar-block">');
  echo('<div class="popup-window" id="flights-calendar-content">');
  echo('<div class="popup-cross">');
  echo('<div class="cross-icon">x</div>');
  echo('</div>');
	
	if ($q_params['direction_type'] == 'one_way')
	{
		$calendar_departure = $q_params['trip'][1]['departure'];
		$calendar_departure_format = format_date(strtotime($q_params['trip'][1]['departure']),'custom','d-m-Y');
		$calendar_departure_price = round($calendar["combinations"][$calendar_departure_format]['price'][$currency_help->get_base_currency()] + $calendar["combinations"][$calendar_departure_format]['commission'][$currency_help->get_base_currency()]);
		$calendar_cheapest_price = $calendar_departure_price;
		$calendar_cheapest_text = '';
		//echo('qqq'.$calendar_departure_price);
		echo('<div align="center" style="padding:20px;">');
		echo('<div class="air-calendar-table">');
		echo('<div style="display:table-row;">');
		echo('<div class="air-calendar-header" align="center">Вылет</div>');
		for ($i=-3;$i<=3;$i++){
			if ($i>0){$day_mark='+';} else{$day_mark='';}
			$days=' '.$day_mark.$i.' days';
			if ($i==-1 or $i==1){$days=' '.$day_mark.$i.' day';}
			if ($i==0){$days='';}
			echo('<div class="air-calendar-arrival" align="center">'.format_date(strtotime($calendar_departure.$days),'custom','d F').'<br>'.mb_convert_case(format_date(strtotime($calendar_departure.$days),'custom','l'), MB_CASE_TITLE, 'UTF-8').'</div>');
		}
		echo('</div>');
		echo('<div style="display:table-row;">');
		echo('<div class="air-calendar-departure"></div>');
		for ($i=-3;$i<=3;$i++){
			if ($i>0){$day_mark='+';} else{$day_mark='';}
			$days=' '.$day_mark.$i.' days';
			if ($i==-1 or $i==1){$days=' '.$day_mark.$i.' day';}
			if ($i==0){$days='';}
			$currentDeparture = format_date(strtotime($calendar_departure.$days),'custom','d-m-Y');
			if (isset($calendar["combinations"][$currentDeparture])){
				if ($q_params["passengers"]["adt"]>0){$adultsCalendar=$q_params["passengers"]["adt"];} else{$adultsCalendar=0;}
				if ($q_params["passengers"]["chd"]>0){$childrenCalendar=$q_params["passengers"]["chd"];} else{$childrenCalendar=0;}
				if ($q_params["passengers"]["inf"]>0){$infantsCalendar=$q_params["passengers"]["inf"];} else{$infantsCalendar=0;}
				$currentPrice = round($calendar["combinations"][$currentDeparture]['price'][$currency_help->get_base_currency()] + $calendar["combinations"][$currentDeparture]['commission'][$currency_help->get_base_currency()]);
				if ($currentPrice < $calendar_departure_price){$bgCalendar = ' style="background:#E7F2F5;"';} else{$bgCalendar='';}
				if ($currentPrice < $calendar_cheapest_price)
				{
					$calendar_cheapest_price = $currentPrice;
					$calendar_cheapest_text = '<span style="font-size:20px;">&larr;</span> &nbsp;Обратите внимание, есть более дешевый перелет на дату '.$currentDeparture;
				}
				echo('<a'.$bgCalendar.' align="center" class="air-calendar-cell" href="/ru/flights/results/c_'.$q_params['trip'][1]['direction_from']["code"].'-c_'.$q_params['trip'][1]['direction_to']["code"].'/'.format_date(strtotime($currentDeparture),'custom','ymd').'/'.$adultsCalendar.$childrenCalendar.$infantsCalendar.'/'.$q_params['cabin_type'].'/0">'.$currency_help->price_html($currentPrice).'<br><img class="air-logo-small" src="'.avis_all_get_logo($calendar["combinations"][$currentDeparture]['airline']).'"></a>');
				}
				else{
					echo('<div class="air-calendar-cell"></div>');
				}
		}
		echo('</div>');
		echo('</div>');
		echo('</div>');
	}

	else {
		$calendar_departure = $q_params['trip'][1]['departure'];
		$calendar_arrival = $q_params['trip'][1]['return'];
		$calendar_departure_format = format_date(strtotime($q_params['trip'][1]['departure']),'custom','d-m-Y');
		$calendar_arrival_format = format_date(strtotime($q_params['trip'][1]['return']),'custom','d-m-Y');
		$calendar_departure_price = round($calendar["combinations"][$calendar_departure_format][$calendar_arrival_format]['price'][$currency_help->get_base_currency()] + $calendar["combinations"][$calendar_departure_format][$calendar_arrival_format]['commission'][$currency_help->get_base_currency()]);
		$calendar_cheapest_price = $calendar_departure_price;
		$calendar_cheapest_text = '';
		echo('<div align="center" style="padding:20px;">');
		echo('<div class="air-calendar-table">');

		for ($i=-4;$i<=3;$i++){
			echo('<div style="display:table-row;">');
			if ($i==-4){
				echo('<div class="air-calendar-header" align="center"><div class="air-calendar-stripe"><svg><line x1="0" y1="0" x2="100%" y2="100%"/></svg><div class="air-calendar-to">Туда</div><div class="air-calendar-back">Обратно</div></div></div>');
				for ($j=-3;$j<=3;$j++){
					if ($j>0){$day_mark='+';} else{$day_mark='';}
					$days=' '.$day_mark.$j.' days';
					if ($j==-1 or $j==1){$days=' '.$day_mark.$j.' day';}
					if ($j==0){$days='';}
					echo('<div class="air-calendar-arrival" align="center">'.format_date(strtotime($calendar_arrival.$days),'custom','d F').'<br>'.mb_convert_case(format_date(strtotime($calendar_arrival.$days),'custom','l'), MB_CASE_TITLE, 'UTF-8').'</div>');
				}
			}
			else{
				if ($i>0){$day_mark='+';} else{$day_mark='';}
				$days=' '.$day_mark.$i.' days';
				if ($i==-1 or $i==1){$days=' '.$day_mark.$i.' day';}
				if ($i==0){$days='';}
				echo('<div class="air-calendar-departure" align="center">'.format_date(strtotime($calendar_departure.$days),'custom','d F').'<br>'.mb_convert_case(format_date(strtotime($calendar_arrival.$days),'custom','l'), MB_CASE_TITLE, 'UTF-8').'</div>');
				$currentDeparture = format_date(strtotime($calendar_departure.$days),'custom','d-m-Y');
	
				for ($j=-3;$j<=3;$j++){
					if ($j>0){$day_mark='+';} else{$day_mark='';}
					$days=' '.$day_mark.$j.' days';
					if ($j==-1 or $j==1){$days=' '.$day_mark.$j.' day';}
					if ($j==0){$days='';}
					$currentArrival = format_date(strtotime($calendar_arrival.$days),'custom','d-m-Y');
					if (isset($calendar["combinations"][$currentDeparture][$currentArrival])){
						if ($q_params["passengers"]["adt"]>0){$adultsCalendar=$q_params["passengers"]["adt"];} else{$adultsCalendar=0;}
						if ($q_params["passengers"]["chd"]>0){$childrenCalendar=$q_params["passengers"]["chd"];} else{$childrenCalendar=0;}
						if ($q_params["passengers"]["inf"]>0){$infantsCalendar=$q_params["passengers"]["inf"];} else{$infantsCalendar=0;}
						$currentPrice = round($calendar["combinations"][$currentDeparture][$currentArrival]['price'][$currency_help->get_base_currency()] + $calendar["combinations"][$currentDeparture][$currentArrival]['commission'][$currency_help->get_base_currency()]);
						if ($currentPrice < $calendar_departure_price){$bgCalendar = ' style="background:#E7F2F5;"';} else{$bgCalendar='';}
						if ($currentPrice < $calendar_cheapest_price)
						{
							$calendar_cheapest_price = $currentPrice;
							$calendar_cheapest_text = '<span style="font-size:20px;">&larr;</span> &nbsp;Обратите внимание, есть более дешевый перелет на даты: туда '.$currentDeparture.', обратно '.$currentArrival;
						}
						echo('<a'.$bgCalendar.' align="center" class="air-calendar-cell" href="/ru/flights/results/c_'.$q_params['trip'][1]['direction_from']["code"].'-c_'.$q_params['trip'][1]['direction_to']["code"].'/'.format_date(strtotime($currentDeparture),'custom','ymd').'-'.format_date(strtotime($currentArrival),'custom','ymd').'/'.$adultsCalendar.$childrenCalendar.$infantsCalendar.'/'.$q_params['cabin_type'].'/1">'.$currency_help->price_html($currentPrice).'<br><img class="air-logo-small" src="'.avis_all_get_logo($calendar["combinations"][$currentDeparture][$currentArrival]['airline']).'"></a>');
					}
					else{
						echo('<div class="air-calendar-cell"></div>');
					}
				}

			}
			echo('</div>');
		}

		echo('</div>');
		echo('</div>');
	}
	echo('</div>');
	echo('</div>');
	echo('</div>');
}

//Приведем данные к нужному виду, для упрощения читаемости шаблона
if(isset($codes['airports']) && !empty($codes['airports'])) {
    $need_timez = array();
    foreach($codes['airports'] as $some_airport) {
        $need_timez[] = $some_airport['city']['code'];
    }
    $timez = db_select('hrk_sf_cities', 'n')
        ->fields('n', array('code', 'tz'))
        ->condition('n.code', $need_timez, 'IN')
        ->execute()
        ->fetchAllKeyed(0,1);

    foreach($timez as $i => $tz) {
      if ($tz == 'Not found') {
        $timez[$i] = 'Europe/Moscow';
      }
    }
}

$i=0;
if ($combinations) {
    foreach ($combinations as $air_code => $airline_combinations) {
        foreach ($airline_combinations as $index => $combination) {
            $price = round($combination['price'][$currency_help->get_base_currency()] + $combination['commission'][$currency_help->get_base_currency()]);
            $air_codes[]  = $combination['validating_airline_code'];
            $price_sort[$i] = $price;
            $combinations_index[$i] = array(
                'owc' => $combination['owc'],
                'provider' => $combination['provider'],
                'airline_code' => $combination['validating_airline_code'],
                'price' => $price,
                'source' => $combination['price']['SOURCE'],
                'flights' => array(),
                'time_in_air' => 0,
                'commission' => $combination['commission'][$currency_help->get_base_currency()],
                'fare_break_down' => $combination['fare_break_down'],
                'transfer_flights' => -count($combination['index_list']),
                'combination_id' => $combination['combination_id'],
                'booking_link' => url('flights/booking/' . $combination['sequence_number'] . '/' . $combination['combination_id'] . '/' . $session['sid'] . '/' . $session['hash']),
            );
            foreach ($combination['index_list'] as $dir => $ref) {
                $comb_flights = $flights[$combination['sequence_number']][$ref][$dir];
                //Считаем транзиты.
                $combinations_index[$i]['transfer_flights'] += count($comb_flights);
                foreach ($comb_flights as $flight_index => $flight) {
                    if(isset($timez[$codes['airports'][$flight['departure_airport']]['city']['code']]) && isset($timez[$codes['airports'][$flight['arrival_airport']]['city']['code']])) {
                        $dep_tz = new DateTimeZone($timez[$codes['airports'][$flight['departure_airport']]['city']['code']]);
                        $ar_tz = new DateTimeZone($timez[$codes['airports'][$flight['arrival_airport']]['city']['code']]);
                        $dep_time = new DateTime(date('Y-m-d H:i:s',$flight['departure']), $dep_tz);
                        $ar_time = new DateTime(date('Y-m-d H:i:s',$flight['arrival']), $ar_tz);
                        $diff_time = date_diff($dep_time, $ar_time);
                        $flight['in_air'] = format_interval(($diff_time->h * 3600) + ($diff_time->i * 60) + $diff_time->s);
                    }

//                    //Собираем данные о полете.
                    //old
//                    $combinations_index[$i]['flights'][] = array(
//                        'arrival' => $flight['arrival'],
//                        'departure' => $flight['departure'],
//                        'city_departure' => $codes['airports'][$flight['departure_airport']]['city']['name_' . $l_prefix],
//                        'city_arrival' => $codes['airports'][$flight['arrival_airport']]['city']['name_' . $l_prefix],
//                        'time' => $flight['in_air']? $flight['in_air']:format_interval($flight['elapsed_time']),
//                        'plain' => $flight['marketing_airline'] . ' ' . $flight['flight_number'],
//                        'design_quantity' => $flight['design_quantity'],
//                      'departure_airport' => $codes['airports'][$flight['departure_airport']]['name_' . $l_prefix],
//                      'departure_airport_code' => $flight['departure_airport'],
//                      'arrival_airport' => $codes['airports'][$flight['arrival_airport']]['name_' . $l_prefix],
//                      'arrival_airport_code' => $flight['arrival_airport'],
//                      'transfer' => ($flight_index > 0 && $flight_index <= count($comb_flights))? 1:0                    //если это пересадка
//                    );

                    if(count($comb_flights) == 1) {
                        $combinations_index[$i]['flights'][$dir] = array(
                            'arrival' => $flight['arrival'],
                            'departure' => $flight['departure'],
                            'city_departure' => $codes['airports'][$flight['departure_airport']]['city']['name_' . $l_prefix],
                            'city_arrival' => $codes['airports'][$flight['arrival_airport']]['city']['name_' . $l_prefix],
                            'time' => format_interval($flight['elapsed_time']),
                            'plain' => $flight['marketing_airline'] . ' ' . $flight['flight_number'],
                            'design_quantity' => $flight['design_quantity'],
                            'departure_airport' => $codes['airports'][$flight['departure_airport']]['name_' . $l_prefix],
                            'departure_airport_code' => $flight['departure_airport'],
                            'arrival_airport' => $codes['airports'][$flight['arrival_airport']]['name_' . $l_prefix],
                            'arrival_airport_code' => $flight['arrival_airport'],
                        );
                    }
                    else if($flight_index == 0) {
                        $combinations_index[$i]['flights'][$dir]['from'] = array(
                            'arrival' => $flight['arrival'],
                            'departure' => $flight['departure'],
                            'city_departure' => $codes['airports'][$flight['departure_airport']]['city']['name_' . $l_prefix],
                            'city_arrival' => $codes['airports'][$flight['arrival_airport']]['city']['name_' . $l_prefix],
                            'time' => format_interval($flight['elapsed_time']),
                            'plain' => $flight['marketing_airline'] . ' ' . $flight['flight_number'],
                            'design_quantity' => $flight['design_quantity'],
                            'departure_airport' => $codes['airports'][$flight['departure_airport']]['name_' . $l_prefix],
                            'departure_airport_code' => $flight['departure_airport'],
                            'arrival_airport' => $codes['airports'][$flight['arrival_airport']]['name_' . $l_prefix],
                            'arrival_airport_code' => $flight['arrival_airport'],
                        );
                    }
                    else if($flight_index > 0 && $flight_index < count($comb_flights) - 1) {
                        $combinations_index[$i]['flights'][$dir]['transfer'][] = array(
                            'arrival' => $flight['arrival'],
                            'departure' => $flight['departure'],
                            'city_departure' => $codes['airports'][$flight['departure_airport']]['city']['name_' . $l_prefix],
                            'city_arrival' => $codes['airports'][$flight['arrival_airport']]['city']['name_' . $l_prefix],
                            'time' => format_interval($flight['elapsed_time']),
                            'plain' => $flight['marketing_airline'] . ' ' . $flight['flight_number'],
                            'design_quantity' => $flight['design_quantity'],
                            'departure_airport' => $codes['airports'][$flight['departure_airport']]['name_' . $l_prefix],
                            'departure_airport_code' => $flight['departure_airport'],
                            'arrival_airport' => $codes['airports'][$flight['arrival_airport']]['name_' . $l_prefix],
                            'arrival_airport_code' => $flight['arrival_airport'],
                        );
                    } else {
                        $combinations_index[$i]['flights'][$dir]['to'] = array(
                            'arrival' => $flight['arrival'],
                            'departure' => $flight['departure'],
                            'city_departure' => $codes['airports'][$flight['departure_airport']]['city']['name_' . $l_prefix],
                            'city_arrival' => $codes['airports'][$flight['arrival_airport']]['city']['name_' . $l_prefix],
                            'time' => format_interval($flight['elapsed_time']),
                            'plain' => $flight['marketing_airline'] . ' ' . $flight['flight_number'],
                            'design_quantity' => $flight['design_quantity'],
                            'departure_airport' => $codes['airports'][$flight['departure_airport']]['name_' . $l_prefix],
                            'departure_airport_code' => $flight['departure_airport'],
                            'arrival_airport' => $codes['airports'][$flight['arrival_airport']]['name_' . $l_prefix],
                            'arrival_airport_code' => $flight['arrival_airport'],
                        );
                    }

                    //Считаем время в полете
                    $combinations_index[$i]['time_in_air'] += ($flight['elapsed_time']);

                }
            }
            $time_in_air_index[] = $combinations_index[$i]['time_in_air'];
            $transfer_index[] = $combinations_index[$i]['transfer_flights'];
            $i++;
        }
    }
}
//Сортируем по цене.
array_multisort($combinations_index, SORT_ASC, SORT_NUMERIC, $price_sort);
?>



<?php if (!empty($combinations_index)): ?>


    <?php
    //Определим минимальную и максимальную цену.
    $min_price = $combinations_index[0]['price'];
    $max_price = $combinations_index[count($combinations_index) - 1]['price'];
    //Определим минимальное и максимальное кол-во трансферов
    sort($transfer_index);
    $min_transfer = $transfer_index[0];
    $max_transfer = $transfer_index[count($transfer_index) - 1];
    //Определим минимальное и максимальное время в полете
    sort($time_in_air_index);
    $min_time = $time_in_air_index[0] / 60;
    $max_time = $time_in_air_index[count($time_in_air_index) - 1] / 60;


    drupal_add_js(array('search_flights' => array(
        'min_price' => $currency_help->get_price($min_price),
        'max_price' => $currency_help->get_price($max_price),
        'min_transfer' => $min_transfer,
        'max_transfer' => $max_transfer,
        'min_time' => $min_time,
        'max_time' => $max_time,
        'currency_prefix' => $currency_prefix,
    )), 'setting');
    ?>

    <div id="filter">
        <div class="container">
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 head_filter">
                <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12">
                    <span><?php print t('Time') ?>:</span>
                    <div id="switcher">
                        <input data-action="departure" type="button" value="<?php print t('Departure', array(), array('context' => 'flights_results')) ?>" class="active"><input data-action="arrival"  type="button" value="<?php print t('Arrival') ?>" class="no_active">
                    </div>
                </div>
                <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12">
                    <span><?php print t('Airlines') ?>:</span>
                    <div class="select_style">
                        <select id="select_air">
                            <option value="none"><?php print t('Any airline') ?></option>
                            <?php
                            $air_codes = array_unique($air_codes);
                            foreach ($air_codes as $code): ?>
                              <?php if (isset($codes['airlines'][$code]['name'])):?>
                                <option value="<?php print $code ?>"><?php print $codes['airlines'][$code]['name'] ?></option>
                              <?php endif ?>
                            <?php endforeach; ?>
                        </select>
                    </div>
                </div>
            </div>
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 footer_filter">
                <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12 filter_input">
                    <label for=""><?php print t('Price') ?>:</label>
                    <div style="position: relative;">
                        <span class="bg_irs"></span>
                        <div class="price">
                            <input type="text" id="price" value="" name="range" />
                        </div>
                    </div>
<!--                    <p>--><?php //print t('Flight ticket cost') ?><!-- (--><?php //print $min_price . $currency_prefix . ' - ' . $max_price . $currency_prefix ?><!--)</p>-->
                  <p><?php print t('Flight ticket cost') ?> (<?php print $currency_help->price_html($min_price) . ' - ' . $currency_help->price_html($max_price) ?>)</p>
                </div>
                <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12 filter_input">
                    <label for=""><?php print t('Amount of transfers') ?>:</label>
                    <div style="position: relative;">
                        <span class="bg_irs"></span>
                        <div class="price">
                            <input type="text" id="transplant" value="" name="range" />
                        </div>
                    </div>
                    <p><?php print t('Transfer flights') ?> (<?php print $min_transfer . ' - ' . $max_transfer ?>) </p>
                </div>
                <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12 filter_input">
                    <label for=""><?php print t('Flight duration') ?>:</label>
                    <div style="position: relative;">
                        <span class="bg_irs"></span>
                        <div class="price">
                            <input type="text" id="travel_time" value="" name="range" />
                        </div>
                    </div>
                    <p><?php print t('Total time in flight') ?> (<?php print $min_time . ' ' . t('min') . ' - ' . $max_time . ' ' . t('min') ?>)</p>
                </div>
            </div>
        </div>
    </div>

		<?php
			if ($calendar) {
		?>
		<div class="container" style="padding-bottom:30px;"><table cellspacing="0" cellpadding="0" border="0"><td valign="center"><a href="#" style="background: #FFA800; padding: 10px 30px; border-radius: 2px; color: #fff; font-weight: bold; border: 0; width: 100%; outline: none !important; margin: 5px 0 0 0;font-size:16px;white-space:nowrap;" id="flights-calendar-button">+/- 3 дня</a></td><td valign="center" style="width:100%;padding-left:20px;font-size:16px;color:#EA4E38;"><?=$calendar_cheapest_text;?></td></table></div> <!-- Сюда вставим кнопку !-->
		<?php
			}
		?>

    <div id="table_air" class="container table-time-departure">

        <div class="filter_table">
            <div id="sort_container">
                <?php foreach ($combinations_index as  $combination): ?>
                    <div class="mix content-row content-row-new" data-date="<?php print $combination['flights'][0]['departure'] ?>" data-wait="<?php print $combination['transfer_flights'] ?>" data-price="<?php print $combination['price'] ?>" data-time="<?php print $combination['time_in_air'] / 60 ?>" data-airline="<?php print $combination['airline_code'] ?>">
                        <div  class="col-lg-12 col-md-12 col-sm-12 col-xs-12 ticket-table-new">
                            <div class="col-lg-2 col-md-2 col-sm-12 col-xs-12 ticket_left_block">
                                <div class="ticket_logo">
                                    <?php $logo = avis_all_get_logo($combination['airline_code']); ?>
                                    <img src="<?php print $logo ?>">
                                </div>
                                <div class="ticket_price">
                                    <?php print $currency_help->price_html($combination['price']) ?>
                                </div>
                                <div class="ticket_buy">
                                    <a href="<?php print $combination['booking_link'] ?>" class="buy"><?php print t('Buy') ?></a>
                                </div>
                                <div class="ticket_left">
                                    <span><?php print t('Free:') ?></span>
                                    <img src="/<?php print $path ?>/images/places_table.png">
                                    <?php
                                    if(!isset($combination['flights'][0]['from'])) {
                                      print $combination['flights'][0]['design_quantity'];
                                    } else {
                                      print $combination['flights'][0]['from']['design_quantity'];
                                    }
                                    //print('<br><br>'.$combination['owc']);
                                    ?>
                                </div>
                            </div>
                            <div class="col-lg-10 col-md-10 col-sm-12 col-xs-12 ticket_right_block">
                                <?php foreach ($combination['flights'] as $id => $flight): ?>
                                    <?php if(isset($flight['from'])):?>
                                        <?php
                                        $from_data = array();
                                        $transfer_data = array();
                                        $to_data = array();
                                        ?>
                                        <?php foreach ($flight as $flight_type => $flight_data) {
                                            switch($flight_type) {
                                                case 'from':
                                                    $from_data['city_departure'] = $flight_data['city_departure'];
                                                    $from_data['departure_airport_code'] = $flight_data['departure_airport_code'];
                                                    $from_data['departure'] = $flight_data['departure'];
                                                    $from_data['plain'] = $flight_data['plain'];
                                                    $from_data['time'] = $flight_data['time'];
                                                    $from_data['departure_airport'] = $flight_data['departure_airport'];
                                                    break;
                                                case 'transfer':
                                                    foreach ($flight_data as $numb => $some_transfer) {
                                                        $transfer_data[$numb]['city_departure'] = $some_transfer['city_departure'];
                                                        $transfer_data[$numb]['departure'] = $some_transfer['departure'];
                                                        $transfer_data[$numb]['departure_airport'] = $some_transfer['departure_airport'];
                                                    }
                                                    break;
                                                case 'to':
                                                    $new_key = count($transfer_data);
                                                    $transfer_data[$new_key]['city_departure'] = $flight_data['city_departure'];
                                                    $transfer_data[$new_key]['departure'] = $flight_data['departure'];
                                                    $transfer_data[$new_key]['departure_airport'] = $flight_data['departure_airport'];

                                                    $to_data['arrival_airport'] = $flight_data['arrival_airport'];
                                                    $to_data['city_arrival'] = $flight_data['city_arrival'];
                                                    $to_data['arrival_airport_code'] = $flight_data['arrival_airport_code'];
                                                    $to_data['arrival'] = $flight_data['arrival'];
                                                    break;
                                            }
                                        }
                                        ?>


                                        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 details_avia_row">
                                            <div class="col-lg-2 col-md-3 col-sm-3 col-xs-12 avia_from_to">
                                                <h4><?php print $from_data['city_departure']; ?></h4>
                                                <p class="airport_code"><?php print $from_data['departure_airport_code']; ?></p>
                                                <p class="dep_date"><i class="glyphicon glyphicon-calendar"></i> <?php print format_date($from_data['departure'], 'custom', 'd F Y') ?></p>
                                                <p class="dep_time"><i class="glyphicon glyphicon-time"></i> <?php print format_date($from_data['departure'], 'custom', 'H:i') ?></p>
                                            </div>
                                            <div class="col-lg-1 col-md-1 col-sm-1 col-xs-12 plain-info">
                                                <i class="glyphicon glyphicon-plane"></i> <?php print $from_data['plain']; ?>
                                            </div>
                                            <div class="col-lg-7 col-md-5 col-sm-5 col-xs-12 fly-info transfers-<?php print count($transfer_data); ?>">
                                                <p class="time-in-air"><?php print $from_data['time']; ?></p>
                                                <div>
                                                <span>
                                                    <i class="glyphicon glyphicon-plane"></i>
                                                    <span class="colapsable-item">
                                                        <span><?php print t('Departure from the airport') ?></span>
                                                        <span><?php print $from_data['departure_airport'] . ', '. $from_data['city_departure']; ?></span>
                                                    </span>
                                                </span>

                                                <?php if(!empty($transfer_data)):?>
                                                    <?php $some_transfer_key = 1 ?>
                                                    <?php foreach ($transfer_data as $some_transfer_data):?>

                                                    <span class="transfer-point-<?php print $some_transfer_key; $some_transfer_key++; ?>">
                                                        <span class="colapsable-item">
                                                            <span><?php print t('Transplant at the airport') ?></span>
                                                            <span><?php print $some_transfer_data['departure_airport'] . ', '. $some_transfer_data['city_departure']; ?></span>
                                                            <span><?php print format_date($some_transfer_data['departure'], 'custom', 'H:i') ?></span>
                                                        </span>
                                                    </span>

                                                    <?php endforeach; ?>
                                                <?php endif; ?>

                                                <span>
                                                    <i class="glyphicon glyphicon-plane"></i>
                                                    <span class="colapsable-item">
                                                        <span><?php print t('Arrival at the airport') ?></span>
                                                        <span><?php print $to_data['arrival_airport'] . ', '. $to_data['city_arrival']; ?></span>
                                                    </span>
                                                </span>

                                                </div>
                                            </div>
                                            <div class="col-lg-2 col-md-3 col-sm-3 col-xs-12 avia_from_to">
                                                <h4><?php print $to_data['city_arrival']; ?></h4>
                                                <p class="airport_code"><?php print $to_data['arrival_airport_code']; ?></p>
                                                <p class="dep_date"><i class="glyphicon glyphicon-calendar"></i> <?php print format_date($to_data['arrival'], 'custom', 'd F Y') ?></p>
                                                <p class="dep_time"><i class="glyphicon glyphicon-time"></i> <?php print format_date($to_data['arrival'], 'custom', 'H:i') ?></p>
                                            </div>
                                        </div>

                                    <?php else: ?>
                                        <!--old code-->
                                    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 details_avia_row">
                                        <div class="col-lg-2 col-md-3 col-sm-3 col-xs-12 avia_from_to">
                                            <h4><?php print $flight['city_departure']; ?></h4>
                                            <p class="airport_code"><?php print $flight['departure_airport_code']; ?></p>
                                            <p class="dep_date"><i class="glyphicon glyphicon-calendar"></i> <?php print format_date($flight['departure'], 'custom', 'd F Y') ?></p>
                                            <p class="dep_time"><i class="glyphicon glyphicon-time"></i> <?php print format_date($flight['departure'], 'custom', 'H:i') ?></p>
                                        </div>
                                        <div class="col-lg-1 col-md-1 col-sm-1 col-xs-12 plain-info">
                                            <i class="glyphicon glyphicon-plane"></i> <?php print $flight['plain']; ?>
                                        </div>
                                        <div class="col-lg-7 col-md-5 col-sm-5 col-xs-12 fly-info">
                                            <p class="time-in-air"><?php print $flight['time']; ?></p>
                                            <div>
                                                <span>
                                                    <i class="glyphicon glyphicon-plane"></i>
                                                    <span class="colapsable-item">
                                                        <span><?php print t('Departure from the airport') ?></span>
                                                        <span><?php print $flight['departure_airport'] . ', '. $flight['city_departure']; ?></span>
                                                    </span>
                                                </span>
                                                <span>
                                                    <i class="glyphicon glyphicon-plane"></i>
                                                    <span class="colapsable-item">
                                                        <span><?php print t('Arrival at the airport') ?></span>
                                                        <span><?php print $flight['arrival_airport'] . ', '. $flight['city_arrival']; ?></span>
                                                    </span>
                                                </span>
                                            </div>
                                        </div>
                                        <div class="col-lg-2 col-md-3 col-sm-3 col-xs-12 avia_from_to">
                                            <h4><?php print $flight['city_arrival']; ?></h4>
                                            <p class="airport_code"><?php print $flight['arrival_airport_code']; ?></p>
                                            <p class="dep_date"><i class="glyphicon glyphicon-calendar"></i> <?php print format_date($flight['arrival'], 'custom', 'd F Y') ?></p>
                                            <p class="dep_time"><i class="glyphicon glyphicon-time"></i> <?php print format_date($flight['arrival'], 'custom', 'H:i') ?></p>
                                        </div>
                                    </div>
                                <?php endif; ?>
                                <?php endforeach; ?>

                                <?php if ($user->uid == '125'): ?>
                                    <div class="debug">
                                        <ul>
                                            <li><b>Валюта билета:</b> <?php print $combination['source']['currency'] ?></li>
                                            <li><b>Общая стоимость билета:</b> <?php print $combination['source']['total_fare'] ?></li>
                                            <span>выведены сырые данные, так как они были получены от Амадеуса</span>
                                        </ul>
                                    </div>
                                <?php endif; ?>
                            </div>
                        </div>

                        <?php if (2 == 1): ?>
                        <!--Cтарая версия-->
                        <div  class="col-lg-12 col-md-12 col-sm-12 col-xs-12 content_table">
                            <table>
                                <tr>
                                  <?php $logo = avis_all_get_logo($combination['airline_code']); ?>
                                    <td class="info"><img class="air-logo" src="<?php print $logo ?>"></td>
                                    <td class="info"><i class="glyphicon glyphicon-plane"></i> <?php print $combination['flights'][0]['plain'] ?></td>
                                    <td class="info">
                                        <i class="glyphicon glyphicon-time"></i>
                                        <span class="time-departure"><?php print format_date($combination['flights'][0]['departure'], 'custom', 'd F Y | H:i') ?></span>
                                        <span class="time-arrival"><?php print format_date($combination['flights'][0]['arrival'], 'custom', 'd F Y | H:i') ?></span>
                                    </td>
                                    <td class="info"><?php print $combination['transfer_flights'] ?> <i class="glyphicon glyphicon-triangle-bottom"></i></td>
                                    <td class="info"></td>
                                    <td class="info">
                                        <a><?php print $q_params['trip'][1]['direction_from']['q'] . ' - ' . $q_params['trip'][1]['direction_to']['q'] ?>
                                        <?php if($q_params['direction_type'] == 'round_trip') print ' - ' . $q_params['trip'][1]['direction_from']['q'];?>
                                        </a>
                                        <?php if ($user->uid == '1') { print $combination['provider']; } ?>
                                    </td>
                                    <td class="info"> <?php print $currency_help->price_html($combination['price']) ?></td>
                                    <td></td>
                                </tr>
                            </table>
                        </div>
                        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 content_table_details">
                            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 details_avia">
                                <?php if ($user->uid == '1'): ?>
                                <div class="debug">
                                    <ul>
                                        <li><b>Валюта билета:</b> <?php print $combination['source']['currency'] ?></li>
                                        <li><b>Общая стоимость билета:</b> <?php print $combination['source']['total_fare'] ?></li>
                                        <span>выведены сырые данные, так как они были получены от Амадеуса</span>
                                    </ul>
                                </div>
                                <?php endif; ?>
                                <?php foreach ($combination['flights'] as $id => $flight): ?>
                                    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 details_avia_row">
                                        <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 avia_to"><i class="glyphicon glyphicon-plane to"></i>
                                            <b><?php print $flight['city_departure']; ?></b><br>
                                            <span><?php print $flight['departure_airport']; ?></span><br>
                                            <span><?php print format_date($flight['departure'], 'custom', 'd F Y | H:i') ?></span></div>
                                        <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12"><?php print $flight['plain']; ?></div>
                                        <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12"><?php print $flight['time']; ?></div>
                                        <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                                            <b><?php print $flight['city_arrival']; ?></b><br>
                                            <?php print $flight['arrival_airport']; ?><br>
                                            <?php print format_date($flight['arrival'], 'custom', 'd F Y | H:i') ?></div>
                                    </div>
                                <?php endforeach; ?>
                            </div>
                        </div>
                        <?php endif;?>
                    </div>
                <?php endforeach; ?>
            </div>
        </div>
    </div>
<?php
    //dd(avis_search_speed_test('Ответ отображен пользователю'));
endif; ?>
