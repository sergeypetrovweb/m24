<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 28.09.14
 * Time: 13:57
 */

class CreditCards {
    private  $_credit_types = array(
        'VI'=>array('name' => 'VISA',
            'type' => 'VI',
            'length' => '16',
            'prefixes' => '4',
            'checkdigit' => true
        ),
        'AX'=>array(
            'name' => 'American Express',
            'type' => 'AX',
            'length' => '15',
            'prefixes' => '34,37',
            'checkdigit' => true
        ),
        'DC'=>array('name' => 'Diners Club',
            'type' => 'DC',
            'length' => '14,16',
            'prefixes' => '36,38,54,55',
            'checkdigit' => true
        ),
        'DS'=>array('name' => 'Discover',
            'type' => 'DS',
            'length' => '16',
            'prefixes' => '6011,622,64,65',
            'checkdigit' => true
        ),
        'JC'=>array('name' => 'JCB',
            'type' => 'JC',
            'length' => '16',
            'prefixes' => '35',
            'checkdigit' => true
        ),
        'CA'=>array('name' => 'MasterCard',
            'type' => 'CA',
            'length' => '16',
            'prefixes' => '51,52,53,54,55',
            'checkdigit' => true
        ),
    );

    public function getCreditsCardList($codes = null){
        $list = array();

        foreach($this->_credit_types as $type=>$creditCardInfo){
            if(empty($codes)){
                $list[$type] = $creditCardInfo['name'];
            }else{
                if(in_array($type,$codes)){
                    $list[$type] = $creditCardInfo['name'];
                }
            }
        }

        return $list;
    }

    public function  isValidCreditCard($cardNumber, $cardName, &$error)
    {

        // Define the cards we support. You may add additional card types.

        //  Name:      As in the selection box of the form - must be same as user's
        //  Length:    List of possible valid lengths of the card number for the card
        //  prefixes:  List of possible prefixes for the card
        //  checkdigit Boolean to say whether there is a check digit

        // Don't forget - all but the last array definition needs a comma separator!

        $cards = $this->_credit_types;
        $ccErrorNo = 0;

        $ccErrors [0] = t("Unknown card type");
        $ccErrors [1] = t("No card number provided");
        $ccErrors [2] = t("Credit card number has invalid format");
        $ccErrors [3] = t("Credit card number is invalid");
        $ccErrors [4] = t("Credit card number is wrong length");

        // Establish card type
        $cardType = -1;

        foreach($cards as $type=>$card){
            // See if it is this card (ignoring the case of the string)
            if (strtolower($cardName) == strtolower($card['name']) || (!empty($card['type']) && strtolower($cardName) == strtolower($card['type']))) {
                $cardType = $type;
                break;
            }
        }

        // If card type not found, report an error
        if ($cardType == -1) {
            $errorNumber = 0;
            $error = $ccErrors [$errorNumber];
            return false;
        }

        // Ensure that the user has provided a credit card number
        if (strlen($cardNumber) == 0) {
            $errorNumber = 1;
            $error = $ccErrors [$errorNumber];
            return false;
        }

        // Remove any spaces from the credit card number
        $cardNo = str_replace(' ', '', $cardNumber);

        // Check that the number is numeric and of the right sort of length.
        if (!preg_match("/^[0-9]{13,19}$/", $cardNo)) {
            $errorNumber = 2;
            $error = $ccErrors [$errorNumber];
            return false;
        }

        // Now check the modulus 10 check digit - if required
        if ($cards[$cardType]['checkdigit']) {
            $checksum = 0; // running checksum total
            // $mychar = ""; // next char to process
            $j = 1; // takes value of 1 or 2

            // Process each digit one by one starting at the right
            for ($i = strlen($cardNo) - 1; $i >= 0; $i--) {

                // Extract the next digit and multiply by 1 or 2 on alternative digits.
                $calc = $cardNo{$i} * $j;

                // If the result is in two digits add 1 to the checksum total
                if ($calc > 9) {
                    $checksum = $checksum + 1;
                    $calc = $calc - 10;
                }

                // Add the units element to the checksum total
                $checksum = $checksum + $calc;

                // Switch the value of j
                if ($j == 1) {
                    $j = 2;
                } else {
                    $j = 1;
                };
            }

            // All done - if checksum is divisible by 10, it is a valid modulus 10.
            // If not, report an error.
            if ($checksum % 10 != 0) {
                $errorNumber = 3;
                $error = $ccErrors [$errorNumber];
                return false;
            }
        }

        // The following are the card-specific checks we undertake.

        // Load an array with the valid prefixes for this card
        $prefix = explode(',', $cards[$cardType]['prefixes']);

        // Now see if any of them match what we have in the card number
        $PrefixValid = false;
        for ($i = 0; $i < sizeof($prefix); $i++) {
            $exp = '/^' . $prefix[$i] . '/';
            if (preg_match($exp, $cardNo)) {
                $PrefixValid = true;
                break;
            }
        }

        // If it isn't a valid prefix there's no point at looking at the length
        if (!$PrefixValid) {
            $errorNumber = 3;
            $error = $ccErrors [$errorNumber];
            return false;
        }

        // See if the length is valid for this card
        $LengthValid = false;
        $lengths = explode(',', $cards[$cardType]['length']);
        for ($j = 0; $j < sizeof($lengths); $j++) {
            if (strlen($cardNo) == $lengths[$j]) {
                $LengthValid = true;
                break;
            }
        }

        // See if all is OK by seeing if the length was valid.
        if (!$LengthValid) {
            $errorNumber = 4;
            $error = $ccErrors [$errorNumber];
            return false;
        };

        // The credit card is in the required format.
        return true;
    }
}

