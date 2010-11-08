<?php

class SalesforceParser extends FeedsParser {
	
	/**
	 * Implementation of FeedsParser::parse().
	 */
	public function parse(FeedsImportBatch $batch, FeedsSource $source) {
		$batch->title = 'hello';
		$batch->description = 'description';
		$batch->link = 'link';
		$batch->items[] = 'item';
	}
	
	public function getMappingSources() {
		return array(
			'title' => array(
				'name' => t('Title'),
				'description' => t('Title of the Salesforce object.'),
				),
			'guid' => array(
				'name' => t('Salesforce ID'),
				'description' => t('Salesforce ID for the object.'),
			),
		) + parent::getMappingSources();
	}
}