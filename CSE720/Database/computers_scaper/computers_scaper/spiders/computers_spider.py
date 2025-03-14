import scrapy
from typing import Iterable
from amazon_scraper.items import AmazonScraperItem
from urllib.parse import urlencode
import os
from dotenv import load_dotenv


class ComputersSpiderSpider(scrapy.Spider):

    name = "computers_spider"
    allowed_domains = ["amazon.com", "www.amazon.com"]
    start_urls = ["https://www.amazon.com"]

    def start_requests(self):
        keyword = ['computers']

        for word in keyword:
            url = f"https://www.amazon.com/s?k={word}"
            yield scrapy.Request(url)

            # yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        computers = response.css('a::attr(href)').getall()
        for comp in computers:
            comp_url = "https://amazon.com" + comp
            yield response.follow(comp_url, callback=self.parse_comp)


    def parse_comp(self, response):
        name = response.css('span#productTitle ::text').get()
        # price = response.css('span.a-price-whole::text').get()
        # rating = response.css('span.a-icon-alt::text').get()}]

        yield {
        "product_name": name.strip() if name else "N/A",
        # "price": price if price else "N/A",
        # "rating": rating if rating else "N/A",
        # "url": response.url
    }




    # def parse_comp(self, response):
    #     name = response.css('span#productTitle::text').get()
    #     yield {"product_name": name}

