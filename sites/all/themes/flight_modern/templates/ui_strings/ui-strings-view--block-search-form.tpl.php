<?php
$img = file_load($settings['img']);
$img = file_create_url($img->uri);
?>

<div id="search" style="background-image: url('<?php print $img ?>')">
    <div class="container">
        <div class="col-lg-8 col-md-8 col-sm-10 col-xs-12 search_block">
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 radio_buttons">
                <input type="radio" class="radio" id="radio_one" name="radio" /><label for="radio_one">Tek Yonde</label>
                <input type="radio" class="radio" id="radio_two" name="radio" /><label for="radio_two">Gedis - Donus</label>
            </div>
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 flights">
                <div class="flight from">
                    <form name="flight_from" method="post">
                        <label for="flight_from">Ucush baslanqici</label>
                        <input type="text" id="flight_from" placeholder="Azerbaijan, Baku, H.Aliyev Airport">
                        <input for="flight_from" value="" class="reset" id="flight_from_reset" type="reset">
                    </form>
                </div>
                <input type="button" id="toogle_flights">
                <div class="flight where">
                    <form name="flight_where" method="post">
                        <label for="flight_where">Ucush noqtesi</label>
                        <input type="text" id="flight_where" placeholder="Kurdemir, Central Airport">
                        <input for="flight_where" value="" class="reset" id="flight_where_reset" type="reset">
                    </form>
                </div>
            </div>
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 dates">
                <div class="date with">
                    <label for="date_with">Baslangic gunu</label>
                    <input type="text" id="date_with" placeholder="Azerbaijan, Baku, H.Aliyev Airport">
                </div>
                <div class="date on">
                    <label for="date_on">Bitis gunu</label>
                    <input type="text" id="date_on" placeholder="Kurdemir, Central Airport">
                </div>
            </div>
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 counts">
                <div class="count">
                    <label>Sernisinlerin sayi</label>
                    <div class="number_count">
                        <img src="/sites/all/themes/flight_modern/images/adults.png">
                        <input id='adults' type='number' value='3'>
                        <a href="#" data-for='adults' data-event='add'></a>
                        <a href="#" data-for='adults' data-event='sub'></a>
                    </div>
                    <div class="number_count">
                        <img src="/sites/all/themes/flight_modern/images/teens.png">
                        <input id='teens' type='number' value='3'>
                        <a href="#" data-for='teens' data-event='add'></a>
                        <a href="#" data-for='teens' data-event='sub'></a>
                    </div>
                    <div class="number_count">
                        <img src="/sites/all/themes/flight_modern/images/children.png">
                        <input id='children' type='number' value='3'>
                        <a href="#" data-for='children' data-event='add'></a>
                        <a href="#" data-for='children' data-event='sub'></a>
                    </div>
                </div>
                <div class="count checks">
                    <label>Ucus sinifi secin</label>
                    <div id="switcher">
                        <input type="button" value="Ekonom" class="active"><input type="button" value="Buisiness" class="no_active">
                    </div>
                </div>
            </div>
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
                <input type="button" value="Bilet axtar" data-toggle="modal" data-target="#loading" class="bilet_axtar">
            </div>

            <!-- Loading -->
            <div class="modal fade" id="loading" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                <div class="modal-dialog">
                    <div class="modal-content">
                        <div class="modal-header">
                            <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                            <a href="index.html"><img src="/sites/all/themes/flight_modern/images/logo.png"></a>
                        </div>
                        <div class="modal-body">
                            <div class="progress">
                                <div class="progress-bar" role="progressbar" aria-valuenow="80" aria-valuemin="0" aria-valuemax="100" style="width: 80%;">
                                    Hazirlanir
                                </div>
                            </div>
                            <p>sevdiyiniz şəhərdə sevdiyiniz<br>hotelleri seçin</p>
                            <img src="/sites/all/themes/flight_modern/images/bg_loading.png">
                        </div>
                    </div>
                </div>
            </div>
            <!-- /Loading -->
        </div>
    </div>
</div>




<div id="social">
    <div class="container">
        <div class="menu_seacrh">
            <ul>
                <li class="active"><a href="#">Avropa Turlari</a></li>
                <li><a href="#">Sagliq turlari</a></li>
                <li><a href="#">Paket turlar</a></li>
                <li><a href="#">Oteller</a></li>
            </ul>
        </div>
        <div class="social">
            Biz Soslial sebekelerde :
            <a href="#"><img src="/sites/all/themes/flight_modern/images/facebook.png"></a>
            <a href="#"><img src="/sites/all/themes/flight_modern/images/twitter.png"></a>
            <a href="#"><img src="/sites/all/themes/flight_modern/images/instagram.png"></a>
        </div>
    </div>
</div>