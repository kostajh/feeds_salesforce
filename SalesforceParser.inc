<?php

class SalesforceParser extends FeedsParser {
	
	/**
	 * Implementation of FeedsParser::parse().
	 */
	public function parse(FeedsImportBatch $batch, FeedsSource $source) {
		
		$result = $batch->getRaw();
		
		$batch->title = 'title';
		$batch->description = 'description';

		
    foreach ($result as $k => $item) {
      $item = feeds_salesforce_flatten_item($item, '', true);

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
	 */
	public function getMappingSources() {
		return array(
			'name' => array(
				'name' => t('Name'),
				'description' => t('Name of the Salesforce object.'),
				),
			'Id' => array(
				'name' => t('Salesforce ID'),
				'description' => t('Salesforce ID for the object.'),
			),
		) + parent::getMappingSources();
	}
}