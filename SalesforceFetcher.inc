<?php

/**
 * Definition of import batch object created by SalesforceFetcher
 */
class FeedsSalesforceBatch extends FeedsImportBatch {
	
	/**
	 * Constructor
	 */
	public function __construct($soql = NULL, $feed_nid) {
		$this->soql = $soql;
		parent::__construct('', $feed_nid);
	}
	
	/**
	 * Implementation of FeedsImportBatch::getRaw();
	 */
	public function getRaw() {
		
		$items = array();
		if ($sf = salesforce_api_connect()) {
			try {
				do {
					if (!isset($response)) {
						$response = $sf->client->query($this->soql);
					} else {
						$response = $sf->client->queryMore($response->queryLocator);
					}
					$items = array_merge($items, $response->records);
				} while (!$response->done);
			}
			catch (Exception $e) {
				drupal_set_message($e->faultstring);
			}
		}
		else {
      watchdog('SalesforceFetcher', t('Could not connect to Salesforce.'), array(), WATCHDOG_ERROR);
    }
		drupal_set_message('<pre>' . print_r($items, true) . '</pre>');
		return $items;
	}
	
}

/**
 * Fetches data from Salesforce.
 */
class SalesforceFetcher extends FeedsFetcher {
	
	/**
	 * Implementation of FeedsFetcher::fetch().
	 */
	public function fetch(FeedsSource $source) {
		$source_config = $source->getConfigFor($this);
		if ($soql = $this->config['soql_query']) {
			return new FeedsSalesforceBatch($soql, $source->feed_nid);
		} else {
    	return new FeedsImportBatch();
		} 
	}
	
	/**
	 * Override parent::configForm().
	 */
	public function configForm(&$form_state) {
		$form = array();
		$form['soql_query'] = array(
		  '#type' => 'textarea',
		  '#title' => t('SOQL query'),
		  '#description' => t('Enter the SOQL query for this feed.'),
		  '#default_value' => $this->config['soql_query'],
		);		
		return $form;
	}
	
	/**
	 * Override parent::configDefaults().
	 */
	public function configDefaults() {
		return array(
			'soql_query' => '',
		);
	}

}