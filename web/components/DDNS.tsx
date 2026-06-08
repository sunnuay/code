import { RefreshCw } from "lucide-react";

const DDNS = () => (
	<div className="bg-white p-6 rounded-xl border border-gray-100 shadow-sm max-w-2xl">
		<h2 className="text-lg font-semibold text-gray-800 mb-6">域名配置</h2>
		<div className="space-y-5">
			<div>
				<label className="block text-sm font-medium text-gray-700 mb-2">
					域名服务商
				</label>
				<select className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none">
					<option>Cloudflare</option>
				</select>
			</div>
			<div>
				<label className="block text-sm font-medium text-gray-700 mb-2">
					域名
				</label>
				<input
					type="text"
					placeholder="example.com"
					className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none"
				/>
			</div>
			<div>
				<label className="block text-sm font-medium text-gray-700 mb-2">
					密钥
				</label>
				<input
					type="password"
					placeholder="API Token"
					className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none"
				/>
			</div>

			<div className="bg-gray-50 p-4 rounded-lg border border-gray-100 flex items-center justify-between mt-6">
				<div>
					<p className="text-sm text-gray-500 mb-1">当前公网 IP</p>
					<p className="font-mono text-gray-800">2606:4700:10::ac42:93f3</p>
				</div>
				<button className="flex items-center px-4 py-2 bg-white border border-gray-200 text-gray-700 hover:bg-gray-50 rounded-lg transition-colors shadow-sm">
					<RefreshCw size={16} className="mr-2" /> 强制同步
				</button>
			</div>
		</div>
	</div>
);

export default DDNS;
