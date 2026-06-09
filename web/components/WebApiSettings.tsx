import { useState, useEffect } from "react";
import { RefreshCw } from "lucide-react";
import type { WebAPIConfig } from "../App";

interface Props {
	config: WebAPIConfig;
	onSave: (c: WebAPIConfig) => void;
	saving: boolean;
	restarting: boolean;
	onRestart: () => void;
}

const WebApiSettings = ({ config, onSave, saving, restarting, onRestart }: Props) => {
	const [local, setLocal] = useState<WebAPIConfig>(config);

	useEffect(() => {
		setLocal(config);
	}, [config]);

	return (
		<div className="bg-white p-6 rounded-xl border border-gray-100 shadow-sm max-w-2xl">
			<h2 className="text-lg font-semibold text-gray-800 mb-6">
				Web API 设置
			</h2>
			<div className="space-y-5">
				<div>
					<label className="block text-sm font-medium text-gray-700 mb-2">
						API 监听地址
					</label>
					<input
						type="text"
						value={local.listen}
						onChange={(e) =>
							setLocal({ ...local, listen: e.target.value })
						}
						disabled={saving}
						className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none"
					/>
				</div>
				<div className="pt-4 flex justify-end">
					<button
						onClick={() => onSave(local)}
						disabled={saving}
						className="flex items-center px-4 py-2 bg-blue-600 text-white hover:bg-blue-700 rounded-lg transition-colors disabled:opacity-50"
					>
						{saving ? "保存中..." : "保存设置"}
					</button>
				</div>
			</div>

			<hr className="mt-6 border-gray-200" />

			<div className="mt-6">
				<h3 className="text-base font-medium text-gray-700 mb-3">
					服务管理
				</h3>
				<button
					onClick={onRestart}
					disabled={restarting}
					className="flex items-center gap-2 px-4 py-2 rounded-lg bg-red-500 hover:bg-red-600 disabled:bg-red-300 text-white text-sm font-medium transition-all duration-200"
				>
					<RefreshCw
						size={16}
						className={restarting ? "animate-spin" : ""}
					/>
					{restarting ? "重启中..." : "重启服务"}
				</button>
			</div>
		</div>
	);
};

export default WebApiSettings;
