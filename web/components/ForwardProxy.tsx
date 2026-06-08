import { Square, RefreshCw } from "lucide-react";

const ForwardProxy = () => (
	<div className="space-y-6">
		<div className="bg-white p-6 rounded-xl border border-gray-100 shadow-sm">
			<div className="flex justify-between items-center mb-6">
				<h2 className="text-lg font-semibold text-gray-800">全局设置</h2>
				<span className="px-3 py-1 bg-green-100 text-green-700 text-sm rounded-full flex items-center">
					<span className="w-2 h-2 bg-green-500 rounded-full mr-2"></span>
					运行中
				</span>
			</div>

			<div className="grid grid-cols-2 gap-6">
				<div>
					<label className="block text-sm font-medium text-gray-700 mb-2">
						监听端口
					</label>
					<input
						type="number"
						defaultValue="9999"
						className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent outline-none"
					/>
				</div>
				<div>
					<label className="block text-sm font-medium text-gray-700 mb-2">
						协议类型
					</label>
					<select className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none">
						<option>HTTP / HTTPS</option>
						<option>SOCKS5</option>
					</select>
				</div>
			</div>

			<div className="mt-6 pt-6 flex justify-end gap-4">
				<button className="flex items-center px-4 py-2 bg-gray-100 text-gray-700 hover:bg-gray-200 rounded-lg transition-colors">
					<Square size={16} className="mr-2" /> 停止服务
				</button>
				<button className="flex items-center px-4 py-2 bg-blue-600 text-white hover:bg-blue-700 rounded-lg transition-colors">
					<RefreshCw size={16} className="mr-2" /> 保存并重启
				</button>
			</div>
		</div>
	</div>
);

export default ForwardProxy;
