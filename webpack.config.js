//import * as path from 'path';
//import * as webpack from 'webpack';
const path = require('path');

var config = {
    // TODO: Add common Configuration
    module: {
		rules: [
   		{
      		test: /\.m?js$/,
      		exclude: /(node_modules|bower_components)/,
      		use: {
        			loader: 'babel-loader',
        			options: {
          			presets: ['@babel/preset-env']
        			}
      		}
    		}
  		]
	}
};

/*
var fooConfig = Object.assign({}, config, {
    name: "a",
    entry: "./a/app",
    output: {
       path: "./a",
       filename: "bundle.js"
    },
});
*/
var barConfig = Object.assign({}, config,{
    name: "a",
    entry: {
    App: "./app/assets/scripts/App.js",
    Vendor: "./app/assets/scripts/Vendor.js"
  },
  	 output: {
    	path: path.resolve(__dirname,"./app/temp/scripts"),
    	filename: "[name].js"
  		},
});

// Return Array of Configurations
module.exports = [
    barConfig,       
];

/*

module.exports = {
  entry: {
    App: "./app/assets/scripts/App.js",
    Vendor: "./app/assets/scripts/Vendor.js"
  },
  output: {
    path: "./app/temp/scripts",
    filename: "[name].js"
  },
	module: {
		rules: [
   		{
      		test: /\.m?js$/,
      		exclude: /(node_modules|bower_components)/,
      		use: {
        			loader: 'babel-loader',
        			options: {
          			presets: ['@babel/preset-env']
        			}
      		}
    		}
  		]
	}
}

*/