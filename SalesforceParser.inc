<?php

class SalesforceParser extends FeedsParser {
	
	/**
	 * Implementation of FeedsParser::parse().
	 */
	public function parse(FeedsImportBatch $batch, FeedsSource $source) {
		
		$result = $batch->getRaw();
		
		$batch->title = 'SOQL query';
		
    foreach ($result as $k => $item) {
      $item = $this->flatten_item($item, '', true);

      $parsed_feed->items[$k] = new stdClass();
      $parsed_feed->items[$k]->options = new stdClass();
      $parsed_feed->items[$k]->options->guid = $item['Id'];
      $parsed_feed->items[$k]->options->raw = $item;

    }
   
		foreach ($parsed_feed->items as $item) {
			$batch->items[] = $item->options->raw;
		}

	}
	
	/**
	 * Implementation of FeedsParser::getMappingSources().
	 * @TODO: Provide dynamic array of options depending on the SOQL query
	 * used in SalesforceFetcher->configForm
	 */
	public function getMappingSources() {
		return FALSE;
		
		// return array(
		// 	'Id' => array(
		// 		'name' => t('Salesforce ID'),
		// 		'description' => t('Salesforce ID for the object.'),
		// 	),
		// 	'Name' => array(
		// 		'name' => t('Name'),
		// 		'description' => t('Name of the Salesforce object.'),
		// 	),
		// ) + parent::getMappingSources();
	}
	
	/**
	 * Recurse and flatten.
	 *
	 * @param $i object to flatten
	 * @param $loc location of $i, using database like dot syntax.
	 * @param $new start a new object.
	 * @return Flattened array version of object.
	 */
	private function flatten_item(&$i, $loc = '', $new = false) {
	  static $item;

	  if ($new) {
	    $item = array();
	  }

	  foreach ($i as $k => $v) {
	    if (is_object($v)) {
	      $this->flatten_item($v, "$loc.$k");
	    }
	    else {
	      $idx = substr("$loc.$k",1);
	      $item[$idx] = $v;
	    }
	  }
	  return $item;
	}
	
}